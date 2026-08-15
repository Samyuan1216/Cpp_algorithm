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
    int n, m, maxv, t;
    std::cin >> n >> m >> maxv >> t;
    --t;

    std::vector<std::vector<std::array<int, 2>>> g(n);
    for (int i = 0, u, v, w; i < m; ++i)
    {
        std::cin >> u >> v >> w;
        --u, --v;

        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    constexpr int INF = 1e9;
    std::vector<std::array<int, 2>> dist(n, {INF, INF});
    dist[t] = {1, 0};

    std::priority_queue<std::pair<std::array<int, 2>, int>, std::vector<std::pair<std::array<int, 2>, int>>, std::greater<>> heap;
    heap.push({dist[t], t});

    while (!heap.empty())
    {
        auto [s, u] = heap.top();
        heap.pop();

        if (s > dist[u])
        {
            continue;
        }

        for (auto &[v, w]: g[u])
        {
            std::array<int, 2> next;
            if (s[1] + w <= maxv)
            {
                next = {s[0], s[1] + w};
            }
            else
            {
                next = {s[0] + 1, w};
            }

            if (next < dist[v])
            {
                dist[v] = next;
                heap.push({dist[v], v});
            }
        }
    }

    for (int u = 0; u < n; ++u)
    {
        std::cout << (dist[u][0] == INF? -1: dist[u][0]) << " \n"[u == n - 1];
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
