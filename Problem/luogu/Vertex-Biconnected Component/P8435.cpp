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

        if (u == v)
        {
            continue;
        }

        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::vector<int> dfn(n, -1), low(n);
    std::vector<std::vector<int>> vbcc;
    std::stack<int> sta;
    int cnt = 0;

    for (int i = 0; i < n; ++i)
    {
        if (dfn[i] != -1)
        {
            continue;
        }

        if (std::ssize(g[i]) == 0)
        {
            vbcc.push_back({});
            vbcc.back().push_back(i);

            continue;
        }

        [&](this auto &&self, int u) -> void
        {
            dfn[u] = low[u] = cnt++;
            sta.push(u);

            for (auto &v: g[u])
            {
                if (dfn[v] == -1)
                {
                    self(v);

                    low[u] = std::min(low[u], low[v]);
                    if (int t; low[v] >= dfn[u])
                    {
                        vbcc.push_back({});
                        vbcc.back().push_back(u);

                        do
                        {
                            t = sta.top();
                            sta.pop();

                            vbcc.back().push_back(t);
                        } while (t != v);
                    }
                }
                else
                {
                    low[u] = std::min(low[u], dfn[v]);
                }
            }
        } (i);
    }

    std::cout << std::ssize(vbcc) << "\n";
    for (auto &s: vbcc)
    {
        std::cout << std::ssize(s);
        for (auto &x: s)
        {
            std::cout << " " << x + 1;
        }
        std::cout << "\n";
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
