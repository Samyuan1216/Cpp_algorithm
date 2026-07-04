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

    std::vector<std::vector<std::array<int, 2>>> g1(n);
    for (int i = 0, u, v, w; i < m; ++i)
    {
        std::cin >> u >> v >> w;
        --u, --v;

        g1[u].push_back({v, w});
    }

    std::vector<int> dfn(n, -1), low(n), belong(n, -1);
    std::stack<int> sta;
    int scc = 0, cnt = 0, s = 0, e = 0;

    [&](this auto &&dfs, int u) -> void
    {
        dfn[u] = low[u] = cnt++;
        sta.push(u);

        for (auto &[v, w]: g1[u])
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
                if (t == 0)
                {
                    s = scc;
                }
                else if (t == n - 1)
                {
                    e = scc;
                }
            } while (t != u);

            ++scc;
        }
    } (0);

    std::vector<std::vector<std::array<int, 2>>> g2(scc);
    for (int u = 0; u < n; ++u)
    {
        for (auto &[v, w]: g1[u])
        {
            if (belong[u] == belong[v])
            {
                continue;
            }

            g2[belong[u]].push_back({belong[v], w});
        }
    }

    auto dijkstra = [&](int n, int s) -> std::vector<int>
    {
        std::vector<int> dist(n, std::numeric_limits<int>::max());
        dist[s] = 0;
    
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> heap;
        heap.push({dist[s], s});
    
        std::vector<bool> visited(n);
        while (!heap.empty())
        {
            auto [wu, u] = heap.top();
            heap.pop();
    
            if (visited[u])
            {
                continue;
            }
    
            visited[u] = true;
            for (auto [v, wv]: g2[u])
            {
                if (!visited[v])
                {
                    if (dist[v] - wv > wu)
                    {
                        dist[v] = wu + wv;
                        heap.push({dist[v], v});
                    }
                }
            }
        }
    
        return dist;
    };

    auto dist = dijkstra(scc, s);
    std::cout << dist[e] << "\n";
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
