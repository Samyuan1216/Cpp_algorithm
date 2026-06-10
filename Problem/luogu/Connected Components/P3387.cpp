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

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    std::vector<std::vector<int>> g1(n);
    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g1[u].push_back(v);
    }

    std::vector<int> dfn(n, -1), low(n), belong(n, -1), weight;
    std::vector<std::vector<int>> scc;
    std::stack<int> sta;
    int cnt = 0;

    for (int i = 0; i < n; ++i)
    {
        if (dfn[i] != -1)
        {
            continue;
        }

        [&](this auto &&dfs, int u) -> void
        {
            dfn[u] = low[u] = cnt++;
            sta.push(u);

            for (auto &v: g1[u])
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

            if (int t, w = 0; dfn[u] == low[u])
            {
                scc.push_back({});
                do
                {
                    t = sta.top();
                    sta.pop();

                    belong[t] = std::ssize(scc) - 1;
                    scc.back().push_back(t);

                    w += arr[t];
                } while (t != u);

                weight.push_back(w);
            }
        } (i);
    }

    std::vector<std::vector<int>> g2(std::ssize(scc));
    std::vector<int> degree(std::ssize(scc));

    for (int u = 0; u < n; ++u)
    {
        for (auto &v: g1[u])
        {
            if (belong[u] == belong[v])
            {
                continue;
            }

            g2[belong[u]].push_back(belong[v]);
            ++degree[belong[v]];
        }
    }

    std::vector<int> dp(std::ssize(scc));
    std::queue<int> q;

    for (int i = 0; i < std::ssize(scc); ++i)
    {
        if (degree[i] == 0)
        {
            q.push(i);
            dp[i] = weight[i];
        }
    }

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto &v: g2[u])
        {
            dp[v] = std::max(dp[v], dp[u] + weight[v]);
            if (--degree[v] == 0)
            {
                q.push(v);
            }
        }
    }

    std::cout << *ranges::max_element(dp) << "\n";
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
