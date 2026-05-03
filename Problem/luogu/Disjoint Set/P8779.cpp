#include <bits/extc++.h>
namespace ranges = std::ranges;
namespace pbds = __gnu_pbds;

using i64 = long long;

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

void solve()
{
    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<int> father(n + 1);
    ranges::iota(father, 0);

    std::vector<i64> dist(n + 1);
    auto find = [&](this auto &&find, int i) -> int
    {
        if (father[i] != i)
        {
            int old = father[i];
            father[i] = find(old);
            dist[i] += dist[old];
        }

        return father[i];
    };

    auto merge = [&](int l, int r, i64 v) -> void
    {
        if (int lf = find(l), rf = find(r); lf != rf)
        {
            father[lf] = rf;
            dist[lf] = dist[r] - dist[l] + v;
        }
    };

    while (m--)
    {
        int l, r;
        i64 s;
        std::cin >> l >> r >> s;

        merge(l - 1, r, s);
    }

    auto query = [&](int l, int r) -> std::optional<i64>
    {
        if (find(l) != find(r))
        {
            return std::nullopt;
        }

        return dist[l] - dist[r];
    };

    while (q--)
    {
        int l, r;
        std::cin >> l >> r;

        if (auto res = query(l - 1, r); res)
        {
            std::cout << *res << "\n";
        }
        else
        {
            std::cout << "UNKNOWN\n";
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
