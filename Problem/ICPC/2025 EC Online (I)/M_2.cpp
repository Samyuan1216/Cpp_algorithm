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

    std::vector<std::vector<std::pair<int, i64>>> g(n);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        i64 w;
        std::cin >> u >> v >> w;
        --u, --v;

        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    std::vector<std::vector<int>> trans(n);
    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        trans[u].push_back(v);
        trans[v].push_back(u);
    }

    std::vector dist(n + 1, std::vector<i64>(n, 1e18));
    dist[0][0] = 0;

    std::priority_queue<std::pair<i64, int>, std::vector<std::pair<i64, int>>, std::greater<>> heap;
    heap.push({0, 0});

    while (!heap.empty())
    {
        auto [d, u] = heap.top();
        heap.pop();

        if (d > dist[0][u])
        {
            continue;
        }

        for (auto &[v, w]: g[u])
        {
            if (dist[0][u] + w < dist[0][v])
            {
                dist[0][v] = dist[0][u] + w;
                heap.push({dist[0][v], v});
            }
        }
    }

    std::vector<i64> ans(n + 1);
    for (int u = 0; u < n; ++u)
    {
        ans[0] += dist[0][u];
    }

    for (int k = 1; k <= n; ++k)
    {
        for (int u = 0; u < n; ++u)
        {
            dist[k][u] = std::min(dist[k][u], dist[k - 1][u]);
            for (auto &v: trans[u])
            {
                dist[k][v] = std::min(dist[k][v], dist[k - 1][u]);
            }
        }

        for (int u = 0; u < n; ++u)
        {
            heap.push({dist[k][u], u});
        }

        while (!heap.empty())
        {
            auto [d, u] = heap.top();
            heap.pop();

            if (d > dist[k][u])
            {
                continue;
            }

            for (auto &[v, w]: g[u])
            {
                if (dist[k][u] + w < dist[k][v])
                {
                    dist[k][v] = dist[k][u] + w;
                    heap.push({dist[k][v], v});
                }
            }
        }

        for (int u = 0; u < n; ++u)
        {
            ans[k] += dist[k][u];
        }
    }

    for (auto &x: ans)
    {
        std::cout << x << "\n";
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
