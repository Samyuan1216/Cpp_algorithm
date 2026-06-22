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
    i64 y;
    std::cin >> n >> m >> y;

    std::vector<std::vector<std::pair<int, i64>>> g(n + 1);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        i64 w;
        std::cin >> u >> v >> w;

        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    for (int i = 1; i <= n; ++i)
    {
        i64 x;
        std::cin >> x;

        g[i].push_back({0, x + y});
        g[0].push_back({i, x});
    }

    auto dijkstra = [&](int n, int s) -> std::vector<i64>
    {
        std::vector<i64> dist(n + 1, 1e18);
        dist[s] = 0;
    
        std::priority_queue<std::pair<i64, int>, std::vector<std::pair<i64, int>>, std::greater<>> heap;
        heap.push({dist[s], s});

        std::vector<bool> visited(n + 1);
        while (!heap.empty())
        {
            auto [wu, u] = heap.top();
            heap.pop();
    
            if (visited[u])
            {
                continue;
            }
    
            visited[u] = true;
            for (auto [v, wv]: g[u])
            {
                if (!visited[v])
                {
                    if (dist[v] - wv > wu)
                    {
                        dist[v] = wu + wv;
                        heap.emplace(dist[v], v);
                    }
                }
            }
        }
    
        return dist;
    };

    auto dist = dijkstra(n, 1);
    for (int i = 2; i <= n; ++i)
    {
        std::cout << dist[i] << " \n"[i == n];
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
