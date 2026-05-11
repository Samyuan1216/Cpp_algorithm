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
    int n, p;
    std::cin >> n >> p;

    std::vector<int> spy(n, -1);
    for (int i = 0, x, w; i < p; ++i)
    {
        std::cin >> x >> w;
        --x;

        spy[x] = w;
    }

    int r;
    std::cin >> r;

    std::vector<std::vector<int>> g(n);
    for (int i = 0, u, v; i < r; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
    }

    std::vector<int> dfn(n, -1), low(n), belong(n, -1);
    std::vector<std::vector<int>> scc;
    std::stack<int> sta;
    int cnt = 0;

    for (int i = 0; i < n; ++i)
    {
        if (dfn[i] != -1 || spy[i] == -1)
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

    for (int i = 0; i < n; ++i)
    {
        if (dfn[i] == -1)
        {
            std::cout << "NO\n";
            std::cout << i + 1 << "\n";

            return;
        }
    }

    std::vector<int> in(std::ssize(scc));
    for (int u = 0; u < n; ++u)
    {
        for (auto &v: g[u])
        {
            if (belong[u] == belong[v])
            {
                continue;
            }

            ++in[belong[v]];
        }
    }

    int ans = 0;
    for (int i = 0; i < std::ssize(scc); ++i)
    {
        if (in[i] != 0)
        {
            continue;
        }

        int min = 1e9;
        for (auto &x: scc[i])
        {
            if (spy[x] >= 0)
            {
                min = std::min(min, spy[x]);
            }
        }

        ans += min;
    }

    std::cout << "YES\n";
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
