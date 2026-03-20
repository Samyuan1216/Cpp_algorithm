#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = int64_t;
using u64 = uint64_t;

template<typename T>
using lim = std::numeric_limits<T>;

#ifndef YUAN_DEBUG
struct __X
{
    __X& operator<<(const auto& str) {return *this;}
    void sp([[maybe_unused]] const std::string& str = "") {}
} dout;
#define debug(x)
#endif

class Seg
{
    struct Info
    {
        u64 sum = 0;
        u64 gcd = 0;
        u64 lcm = 0;
        u64 change = 0;
        bool update = false;
    };

    std::vector<Info> info;

    void lazy(int i, u64 v, int n)
    {
        info[i] = {n * v, v, v, v, true};
    }

    void up(int i)
    {
        info[i].sum = info[i << 1].sum + info[i << 1 | 1].sum;
        info[i].gcd = std::gcd(info[i << 1].gcd, info[i << 1 | 1].gcd);
        info[i].lcm = std::lcm(info[i << 1].lcm, info[i << 1 | 1].lcm);
    }

    void down(int i, int ln, int rn)
    {
        if (info[i].update)
        {
            lazy(i << 1, info[i].change, ln);
            lazy(i << 1 | 1, info[i].change, rn);

            info[i].update = false;
        }
    }
public:
    Seg(const auto &arr, int size): info(4 * size + 1)
    {
        auto build = [&](auto &&self, int l, int r, int i) -> void
        {
            if (l == r)
            {
                info[i].sum = info[i].gcd = info[i].lcm = arr[l];
                return;
            }

            int mid = std::midpoint(l, r);
            self(self, l, mid, i << 1);
            self(self, mid + 1, r, i << 1 | 1);

            up(i);
        };

        build(build, 1, size, 1);
    }

    void update(const int &jobl, const int &jobr, const u64 &jobv, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            lazy(i, jobv, r - l + 1);
            return;
        }

        int mid = std::midpoint(l, r);
        down(i, mid - l + 1, r - mid);

        if (mid >= jobl)
        {
            update(jobl, jobr, jobv, l, mid, i << 1);
        }

        if (mid + 1 <= jobr)
        {
            update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }

        up(i);
    }

    u64 query(const int &jobl, const int &jobr, const u64 &jobv, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            if (jobv % info[i].lcm == 0)
            {
                return info[i].sum;
            }

            if (info[i].gcd == info[i].lcm)
            {
                u64 new_val = std::gcd(info[i].gcd, jobv), res = new_val * (r - l + 1);
                lazy(i, new_val, r - l + 1);

                return res;
            }
        }

        int mid = std::midpoint(l, r);
        down(i, mid - l + 1, r - mid);

        u64 res = 0;
        if (mid >= jobl)
        {
            res += query(jobl, jobr, jobv, l, mid, i << 1);
        }

        if (mid + 1 <= jobr)
        {
            res += query(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }

        up(i);
        return res;
    }
};

void solve()
{
    int n, q;
    std::cin >> n >> q;

    auto arr = std::vector<u64>(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];
    }

    Seg tr(arr, n);
    while (q--)
    {
        int op, l, r;
        u64 x;
        std::cin >> op >> l >> r >> x;

        if (op == 0)
        {
            tr.update(l, r, x, 1, n, 1);
        }
        else
        {
            std::cout << tr.query(l, r, x, 1, n, 1) << "\n";
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    std::cin >> t;
    while (t--)
    {
        solve();
    }
}
