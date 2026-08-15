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
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<int, i64>>> g(n);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        i64 w;
        std::cin >> u >> v >> w;
        --u, --v;

        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    std::vector<std::vector<int>> trans(n);
    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        trans[u].push_back(v);
        trans[v].push_back(u);
    }

    std::vector dp(n + 1, std::vector<i64>(n));
    [&](this auto &&self, int u, int f, i64 d) -> void
    {
        dp[0][u] = d;
        for (auto &[v, w]: g[u])
        {
            if (v == f)
            {
                continue;
            }

            self(v, u, d + w);
        }
    } (0, 0, 0);

    std::vector<i64> ans(n + 1);
    for (int u = 0; u < n; ++u)
    {
        ans[0] += dp[0][u];
    }

    for (int k = 1; k <= n; ++k)
    {
        auto f = dp[k - 1];
        for (int u = 0; u < n; ++u)
        {
            for (auto &v: trans[u])
            {
                f[v] = std::min(f[v], dp[k - 1][u]);
            }
        }

        std::vector<i64> down(n);
        [&](this auto &&self, int u, int fa) -> void
        {
            down[u] = f[u];
            for (auto &[v, w]: g[u])
            {
                if (v == fa)
                {
                    continue;
                }

                self(v, u);

                down[u] = std::min(down[u], down[v] + w);
            }
        } (0, 0);

        std::vector<i64> up(n, 1e18);
        [&](this auto &&self, int u, int fa) -> void
        {
            i64 min = f[u], submin = 1e18;
            int min_u = -1;

            for (auto &[v, w]: g[u])
            {
                if (v == fa)
                {
                    continue;
                }

                if (i64 val = down[v] + w; val < min)
                {
                    submin = min;
                    min = val;
                    min_u = v;
                }
                else if (val < submin)
                {
                    submin = val;
                }
            }

            for (auto &[v, w]: g[u])
            {
                if (v == fa)
                {
                    continue;
                }

                i64 best = (v == min_u? submin: min);
                up[v] = std::min(up[u], best) + w;

                self(v, u);
            }
        } (0, 0);

        for (int u = 0; u < n; ++u)
        {
            dp[k][u] = std::min(down[u], up[u]);
            ans[k] += dp[k][u];
        }
    }

    for (auto &x: ans)
    {
        std::cout << x << "\n";
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
