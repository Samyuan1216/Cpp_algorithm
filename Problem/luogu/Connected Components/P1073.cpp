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

    std::vector<int> cost(n);
    for (auto &x: cost)
    {
        std::cin >> x;
    }

    std::vector<std::vector<int>> g(n);
    for (int i = 0, u, v, z; i < m; ++i)
    {
        std::cin >> u >> v >> z;
        --u, --v;

        g[u].push_back(v);
        if (z == 2)
        {
            g[v].push_back(u);
        }
    }

    std::vector<int> dfn(n, -1), low(n), belong(n, -1);
    std::vector<std::array<int, 2>> scc;
    std::stack<int> sta;
    int cnt = 0;

    [&](this auto &&dfs, int u) -> void
    {
        dfn[u] = low[u] = cnt++;
        sta.push(u);

        for (auto &v: g[u])
        {
            if (dfn[v] == -1)
            {
                dfs(v);

                low[u] = std::min(low[u], low[v]);
            }
            else if (belong[v] == -1)
            {
                low[u] = std::min(low[u], dfn[v]);
            }
        }

        if (int t; dfn[u] == low[u])
        {
            scc.push_back({100, 0});
            do
            {
                t = sta.top();
                sta.pop();

                belong[t] = std::ssize(scc) - 1;
                scc.back()[0] = std::min(scc.back()[0], cost[t]);
                scc.back()[1] = std::max(scc.back()[1], cost[t]);
            } while (t != u);
        }
    } (0);

    if (belong[n - 1] == -1)
    {
        std::cout << 0 << "\n";
        return;
    }

    std::vector<std::vector<int>> g2(std::ssize(scc));
    std::vector<int> degree(std::ssize(scc));

    for (int u = 0; u < n; ++u)
    {
        if (belong[u] == -1)
        {
            continue;
        }

        for (auto &v: g[u])
        {
            if (belong[v] == -1 || belong[u] == belong[v])
            {
                continue;
            }

            g2[belong[u]].push_back(belong[v]);
            ++degree[belong[v]];
        }
    }

    std::vector<std::optional<bool>> can(std::ssize(scc));
    auto check = [&](this auto &&dfs, int u) -> std::optional<bool>
    {
        if (u == belong[n - 1])
        {
            return true;
        }

        if (can[u].has_value())
        {
            return can[u];
        }

        for (auto &v: g2[u])
        {
            if (*dfs(v))
            {
                can[u] = true;
                return can[u];
            }
        }

        can[u] = false;
        return can[u];
    };

    constexpr int INF = 1e9;
    std::vector<int> dp(std::ssize(scc), INF);
    dp[belong[0]] = scc[belong[0]][0];

    int ans = 0;
    std::queue<int> q;

    for (int i = 0; i < std::ssize(scc); ++i)
    {
        if (degree[i] == 0)
        {
            q.push(i);
        }
    }

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        if (dp[u] != INF)
        {
            dp[u] = std::min(dp[u], scc[u][0]);
            if (*check(u))
            {
                ans = std::max(ans, scc[u][1] - dp[u]);
            }
        }

        for (auto &v: g2[u])
        {
            dp[v] = std::min(dp[v], dp[u]);
            if (--degree[v] == 0)
            {
                q.push(v);
            }
        }
    }

    std::cout << ans << "\n";
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
