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

    std::vector<std::vector<int>> g(n);
    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
    }

    std::vector<i64> weight(n);
    for (auto &x: weight)
    {
        std::cin >> x;
    }

    int s, pn;
    std::cin >> s >> pn;
    --s;

    std::vector<int> p(pn);
    for (auto &x: p)
    {
        std::cin >> x;
        --x;
    }

    std::vector<int> dfn(n, -1), low(n), belong(n, -1);
    std::vector<i64> scc_weight;
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
            scc_weight.push_back(0);
            do
            {
                t = sta.top();
                sta.pop();

                belong[t] = std::ssize(scc_weight) - 1;
                scc_weight.back() += weight[t];
            } while (t != u);
        }
    } (s);

    std::vector<std::vector<int>> g2(std::ssize(scc_weight));
    std::vector<int> degree(std::ssize(scc_weight));

    for (int u = 0; u < n; ++u)
    {
        if (belong[u] == -1)
        {
            continue;
        }

        for (auto &v: g[u])
        {
            if (belong[u] == -1)
            {
                continue;
            }

            if (belong[u] == belong[v])
            {
                continue;
            }

            g2[belong[u]].push_back(belong[v]);
            ++degree[belong[v]];
        }
    }

    std::vector<i64> dp(std::ssize(scc_weight), -1);
    dp[belong[s]] = scc_weight[belong[s]];

    std::queue<int> q;
    for (int i = 0; i < std::ssize(scc_weight); ++i)
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

        if (dp[u] == -1)
        {
            continue;
        }

        for (auto &v: g2[u])
        {
            dp[v] = std::max(dp[v], dp[u] + scc_weight[v]);
            if (--degree[v] == 0)
            {
                q.push(v);
            }
        }
    }

    i64 ans = 0;
    for (auto &x: p)
    {
        if (belong[x] == -1)
        {
            continue;
        }

        ans = std::max(ans, dp[belong[x]]);
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
