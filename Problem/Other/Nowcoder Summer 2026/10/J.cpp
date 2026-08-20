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

    std::vector<std::vector<std::array<int, 2>>> g(n);
    std::vector<std::array<int, 2>> edges(m);

    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back({v, i});
        g[v].push_back({u, i});
        edges[i] = {u, v};
    }

    std::vector<int> dfn(n, -1), low(n), ans(n), degree(n);
    std::stack<int> sta;
    int cnt = 0;

    for (int i = 0; i < n; ++i)
    {
        if (dfn[i] != -1)
        {
            continue;
        }

        [&](this auto &&self, int u, int pre) -> void
        {
            dfn[u] = low[u] = cnt++;
            for (auto &[v, id]: g[u])
            {
                if (id == pre)
                {
                    continue;
                }

                if (dfn[v] == -1)
                {
                    sta.push(id);

                    self(v, id);

                    low[u] = std::min(low[u], low[v]);
                    if (int t; low[v] >= dfn[u])
                    {
                        std::vector<int> touched;
                        do
                        {
                            t = sta.top();
                            sta.pop();

                            if (degree[edges[t][0]] == 0)
                            {
                                touched.push_back(edges[t][0]);
                            }

                            ++degree[edges[t][0]];

                            if (degree[edges[t][1]] == 0)
                            {
                                touched.push_back(edges[t][1]);
                            }

                            ++degree[edges[t][1]];
                        } while (t != id);

                        for (auto &x: touched)
                        {
                            ans[x] += degree[x] / 2;
                            degree[x] = 0;
                        }
                    }
                }
                else if (dfn[v] < dfn[u])
                {
                    sta.push(id);
                    low[u] = std::min(low[u], dfn[v]);
                }
            }
        } (i, -1);
    }

    for (int i = 0; i < n; ++i)
    {
        std::cout << ans[i] << " \n"[i == n - 1];
    }
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
