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
    constexpr int n = 30000;

    std::vector<int> father(n), size(n, 1), dist(n);
    ranges::iota(father, 0);

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

    auto merge = [&](int l, int r) -> void
    {
        if (int lf = find(l), rf = find(r); lf != rf)
        {
            father[lf] = rf;
            dist[lf] += size[rf];
            size[rf] += size[lf];
        }
    };

    auto query = [&](int l, int r) -> int
    {
        if (find(l) != find(r))
        {
            return -1;
        }

        return std::abs(dist[l] - dist[r]) - 1;
    };

    int t;
    std::cin >> t;

    while (t--)
    {
        char op;
        int i, j;
        std::cin >> op >> i >> j;
        --i, --j;

        if (op == 'M')
        {
            merge(i, j);
        }
        else
        {
            std::cout << query(i, j) << "\n";
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
