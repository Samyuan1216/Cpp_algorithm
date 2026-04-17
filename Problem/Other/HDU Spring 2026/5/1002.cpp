#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

template<typename T>
using lim = std::numeric_limits<T>;

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

    auto dist = [&](int n, int s) -> std::vector<int>
    {
        using pq = std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>>;
        auto heap = pq();
    
        auto dist = std::vector(n, lim<int>::max());
        auto visited = std::vector<bool>(n);
    
        dist[s] = 0;
        heap.push({dist[s], s});
    
        while (!heap.empty())
        {
            auto [wu, u] = heap.top();
            heap.pop();
    
            if (visited[u])
            {
                continue;
            }
    
            visited[u] = true;
            dist[u] = std::max(dist[u], u);
            for (auto v: g[u])
            {
                if (!visited[v])
                {
                    if (dist[u] < dist[v])
                    {
                        dist[v] = dist[u];
                        heap.push({dist[v], v});
                    }
                }
            }
        }
    
        return dist;
    } (n, 0);

    for (int i = 0; i < n; ++i)
    {
        std::cout << (dist[i] != lim<int>::max()? dist[i] + 1: -1) << " \n"[i == n - 1];
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
