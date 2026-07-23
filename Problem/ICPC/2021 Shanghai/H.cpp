#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

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

    std::vector<i64> val(n << 1);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> val[i];
    }

    std::vector<std::array<i64, 3>> edges(m);
    for (auto &[w, u, v]: edges)
    {
        std::cin >> u >> v >> w;
        --u, --v;
    }

    ranges::sort(edges);

    std::vector<int> father(n << 1);
    ranges::iota(father, 0);

    auto find = [&](this auto &&find, int i) -> int
    {
        return (father[i] = (father[i] == i? i: find(father[i])));
    };

    constexpr int limit = 20;
    auto stjump = std::vector(n << 1, std::vector<int>(limit));
    auto stmax = std::vector(n << 1, std::vector<i64>(limit));

    int cnt = n;
    for (int i = 0; i < m; ++i)
    {
        if (int fx = find(edges[i][1]), fy = find(edges[i][2]); fx != fy)
        {
            father[fx] = father[fy] = cnt;
            val[cnt] = val[fx] + val[fy];

            stjump[fx][0] = cnt;
            stmax[fx][0] = edges[i][0] - val[fx];

            stjump[fy][0] = cnt;
            stmax[fy][0] = edges[i][0] - val[fy];

            ++cnt;
        }
    }

    stjump[cnt - 1][0] = cnt - 1;
    stmax[cnt - 1][0] = 2e18;

    for (int p = 1; p < limit; ++p)
    {
        for (int i = 0; i < cnt; ++i)
        {
            stjump[i][p] = stjump[stjump[i][p - 1]][p - 1];
            stmax[i][p] = std::max(stmax[i][p - 1], stmax[stjump[i][p - 1]][p - 1]);
        }
    }

    while (q--)
    {
        int x;
        i64 k;
        std::cin >> x >> k;
        --x;

        for (int p = limit - 1; p >= 0; --p)
        {
            if (stmax[x][p] <= k)
            {
                x = stjump[x][p];
            }
        }

        std::cout << k + val[x] << "\n";
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
