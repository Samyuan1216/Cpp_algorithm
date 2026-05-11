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

    std::vector<std::vector<int>> g1(n);
    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g1[u].push_back(v);
    }

    std::vector<int> dfn(n, -1), low(n), belong(n, -1);
    std::stack<int> sta;
    int cnt = 0, scc = 0;

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

            if (int t; dfn[u] == low[u])
            {
                do
                {
                    t = sta.top();
                    sta.pop();

                    belong[t] = scc;
                } while (t != u);

                ++scc;
            }
        } (i);
    }

    std::vector<std::vector<int>> g2(scc);
    std::vector<int> indegree(scc);

    for (int u = 0; u < n; ++u)
    {
        for (auto &v: g1[u])
        {
            if (belong[u] == belong[v])
            {
                continue;
            }

            g2[belong[u]].push_back(belong[v]);
            ++indegree[belong[v]];
        }
    }

    std::queue<int> u;
    for (int i = 0; i < scc; ++i)
    {
        if (indegree[i] == 0)
        {
            u.push(i);
        }
    }

    while (!u.empty())
    {
        if (std::ssize(u) > 1)
        {
            std::cout << "No\n";
            return;
        }

        int t = u.front();
        u.pop();

        for (auto &v: g2[t])
        {
            if (--indegree[v] == 0)
            {
                u.push(v);
            }
        }
    }

    std::cout << "Yes\n";
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
