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
    std::vector<std::array<int, 3>> edges(m);

    for (auto &[a, u, v]: edges)
    {
        int w;
        std::cin >> u >> v >> w >> a;
        --u, --v;

        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    auto dijkstra = [&](int n, int s) -> std::vector<int>
    {
        std::vector<int> dist(n, 2e9 + 10);
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
            for (auto [v, wv]: g[u])
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

    auto dist = dijkstra(n, 0);
    ranges::sort(edges, std::greater());

    std::vector<int> father(2 * n);
    ranges::iota(father, 0);

    auto find = [&](this auto &&find, int i) -> int
    {
        return (father[i] = (father[i] == i? i: find(father[i])));
    };

    std::vector<std::vector<int>> g2(2 * n);
    std::vector<int> height(2 * n, 2e9);
    int cnt = n;

    for (int i = 0; i < m; ++i)
    {
        if (int fx = find(edges[i][1]), fy = find(edges[i][2]); fx != fy)
        {
            father[fx] = father[fy] = cnt;
            height[cnt] = edges[i][0];

            g2[cnt].push_back(fx);
            g2[cnt].push_back(fy);

            ++cnt;
        }
    }

    constexpr int limit = 20;
    auto stjump = std::vector(2 * n, std::vector<int>(limit));
    std::vector<int> min(2 * n);

    [&](this auto &&dfs, int u, int f) -> void
    {
        stjump[u][0] = f;
        min[u] = (u < n? dist[u]: 2e9);

        for (auto &v: g2[u])
        {
            dfs(v, u);

            min[u] = std::min(min[u], min[v]);
        }
    } (cnt - 1, cnt - 1);

    for (int p = 1; p < limit; ++p)
    {
        for (int i = 0; i < cnt; ++i)
        {
            stjump[i][p] = stjump[stjump[i][p - 1]][p - 1];
        }
    }

    int q, k, s;
    std::cin >> q >> k >> s;

    int last = 0;
    while (q--)
    {
        int v, p;
        std::cin >> v >> p;

        v = (v + k * last - 1) % n;
        p = (p + k * last) % (s + 1);

        for (int i = limit - 1; i >= 0; --i)
        {
            if (height[stjump[v][i]] > p)
            {
                v = stjump[v][i];
            }
        }

        last = min[v];
        std::cout << last << "\n";
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
