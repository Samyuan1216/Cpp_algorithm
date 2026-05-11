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
    for (int i = 0, a, b, t; i < m; ++i)
    {
        std::cin >> a >> b >> t;
        --a, --b;

        g[a].push_back(b);
        if (t == 2)
        {
            g[b].push_back(a);
        }
    }

    std::vector<int> dfn(n, -1), low(n), belong(n, -1);
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
                scc.push_back({});

                do
                {
                    t = sta.top();
                    sta.pop();

                    belong[t] = std::ssize(scc) - 1;
                    scc.back().push_back(t);
                } while (t != u);
            }
        } (i);
    }

    for (auto &line: scc)
    {
        ranges::sort(line);
    }

    ranges::sort(scc, {}, [](const auto &a) { return std::tuple{-std::ssize(a), a[0]}; });

    std::cout << std::ssize(scc[0]) << "\n";
    for (int i = 0; i < std::ssize(scc[0]); ++i)
    {
        std::cout << scc[0][i] + 1 << " \n"[i == std::ssize(scc[0]) - 1];
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
