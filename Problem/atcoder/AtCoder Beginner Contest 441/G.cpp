#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = int64_t;

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
        i64 max, add;
        bool update, reverse, clear;
        int flipped;

        Info(): max(0), add(0), update(false), reverse(false), clear(false), flipped(2) {}
    };

    std::vector<Info> info;

    void max_lazy(int i, i64 v)
    {
        if (info[i].flipped != 0)
        {
            info[i].max += v;
            info[i].add += v;
            info[i].update = true;
        }
    }

    void clear_lazy(int i)
    {
        info[i].max = 0;
        info[i].add = 0;
        info[i].update = false;
        info[i].clear = true; 
    }

    void flip_lazy(int i)
    {
        info[i].reverse = !info[i].reverse;

        if (info[i].flipped == 0)
        {
            info[i].flipped = 2;
        }
        else if (info[i].flipped == 2)
        {
            info[i].flipped = 0;
        }
    }

    void up(int i)
    {
        int ls = i << 1, rs = i << 1 | 1;
        info[i].max = std::max(info[ls].max, info[rs].max);

        if (info[ls].flipped != info[rs].flipped)
        {
            info[i].flipped = 1;
        }
        else
        {
            info[i].flipped = info[ls].flipped;
        }
    }

    void down(int i)
    {
        int ls = i << 1, rs = i << 1 | 1;

        if (info[i].clear)
        {
            clear_lazy(ls);
            clear_lazy(rs);
            info[i].clear = false;
        }

        if (info[i].reverse)
        {
            flip_lazy(ls);
            flip_lazy(rs);
            info[i].reverse = false;
        }

        if (info[i].update)
        {
            max_lazy(ls, info[i].add);
            max_lazy(rs, info[i].add);
            info[i].add = 0;
            info[i].update = false;
        }
    }

public:
    Seg(int size): info((size + 1) << 2) {}

    void add(int jobl, int jobr, i64 jobv, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            max_lazy(i, jobv);
            return;
        }
        
        int mid = l + (r - l) / 2;
        down(i);

        if (jobl <= mid)
        {
            add(jobl, jobr, jobv, l, mid, i << 1);
        }

        if (jobr > mid)
        {
            add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }

        up(i);
    }

    void reverse(int jobl, int jobr, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            clear_lazy(i);
            flip_lazy(i);
            return;
        }
        
        int mid = l + (r - l) / 2;
        down(i);

        if (jobl <= mid)
        {
            reverse(jobl, jobr, l, mid, i << 1);
        }

        if (jobr > mid)
        {
            reverse(jobl, jobr, mid + 1, r, i << 1 | 1);
        }

        up(i);
    }

    i64 query(int jobl, int jobr, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            return info[i].max;
        }

        int mid = l + (r - l) / 2;
        down(i);

        i64 ans = lim<i64>::min();
        if (jobl <= mid)
        {
            ans = std::max(ans, query(jobl, jobr, l, mid, i << 1));
        }

        if (jobr > mid)
        {
            ans = std::max(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));
        }

        return ans;
    }
};

void solve()
{
    int n, q;
    std::cin >> n >> q;

    Seg tree(n);
    while (q--)
    {
        int op, l, r;
        std::cin >> op >> l >> r;

        if (op == 1)
        {
            i64 x;
            std::cin >> x;
            tree.add(l, r, x, 1, n, 1);
        }
        else if (op == 2)
        {
            tree.reverse(l, r, 1, n, 1);
        }
        else
        {
            std::cout << tree.query(l, r, 1, n, 1) << "\n";
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    while (t--)
    {
        solve();
    }
}
