#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

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
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    --s, --t;

    std::vector<std::vector<std::array<int, 2>>> g(n);
    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back({v, 0});
    }

    for (auto &t: g)
    {
        ranges::sort(t);

        for (int j = 1; j < std::ssize(t); ++j)
        {
            t[j][1] = 1;
        }
    }

    constexpr int INF = 1e9;
    auto dijkstra = [&]() -> std::vector<int>
    {
        std::priority_queue<std::array<int, 2>, std::vector<std::array<int, 2>>, std::greater<>> heap;
        heap.push({0, s});

        std::vector<int> dist(n, INF);
        dist[s] = 0;

        std::vector<bool> vis(n);
        while (!heap.empty())
        {
            auto [d, u] = heap.top();
            heap.pop();

            if (vis[u])
            {
                continue;
            }

            vis[u] = true;
            for (auto &[v, w]: g[u])
            {
                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    heap.push({dist[v], v});
                }
            }
        }

        return dist;
    };

    auto dist = dijkstra();
    std::cout << (dist[t] == INF? -1: dist[t]) << "\n";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    // std::cin >> t;
    while (t--)
    {
        solve();
    }
}