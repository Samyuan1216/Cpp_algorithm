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
    int n, m, s;
    std::cin >> n >> m >> s;
    --s;

    std::vector<std::vector<int>> g(n);
    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    int cnt = 0, limit = std::bit_width(unsigned(2 * n - 1));
    auto rmq = std::vector(2 * n - 1, std::vector<int>(limit));
    std::vector<int> dfn(n);

    [&](this auto &&dfs, int u, int f) -> void
    {
        dfn[u] = cnt++;
        rmq[dfn[u]][0] = f;

        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            dfs(v, u);
        }
    } (s, s);

    auto up = [&](int x, int y) -> int
    {
        return (dfn[x] < dfn[y]? x: y);
    };

    for (int pre = 0, cur = 1; cur < limit; ++pre, ++cur)
    {
        for (int i = 0; i + (1 << cur) - 1 < cnt; ++i)
        {
            rmq[i][cur] = up(rmq[i][pre], rmq[i + (1 << pre)][pre]);
        }
    }

    auto lca = [&](int x, int y) -> int
    {
        if (x == y)
        {
            return x;
        }

        x = dfn[x], y = dfn[y];
        if (x > y)
        {
            std::swap(x, y);
        }
        ++x;

        int k = std::bit_width(unsigned(y - x + 1)) - 1;
        return up(rmq[x][k], rmq[y - (1 << k) + 1][k]);
    };

    while (m--)
    {
        int u, v;
        std::cin >> u >> v;
        --u, --v;

        std::cout << lca(u, v) + 1 << "\n";
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
