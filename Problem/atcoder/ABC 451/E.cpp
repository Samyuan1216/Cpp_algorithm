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
    int n;
    std::cin >> n;

    auto g = std::vector(n, std::vector<int>(n));
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            std::cin >> g[i][j];

            g[j][i] = g[i][j];
        }
    }

    auto tr = std::vector(n, std::vector<std::array<int, 2>>());
    for (int i = 1; i < n; ++i)
    {
        int parent = -1, min_dist = lim<int>::max();
        for (int j = 0; j < n; ++j)
        {
            if (i == j)
            {
                continue;
            }

            if (g[0][j] + g[j][i] == g[0][i] && g[j][i] < min_dist)
            {
                parent = j;
                min_dist = g[j][i];
            }
        }

        if (parent == -1)
        {
            std::cout << "No\n";
            return;
        }

        tr[i].push_back({parent, g[i][parent]});
        tr[parent].push_back({i, g[i][parent]});
    }

    auto bfs = [&](int s) -> bool
    {
        auto q = std::queue<int>();
        auto dist = std::vector<int>(n, -1);

        q.push(s);
        dist[s] = 0;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (auto [v, w]: tr[u])
            {
                if (dist[v] != -1)
                {
                    continue;
                }

                dist[v] = dist[u] + w;
                q.push(v);
            }
        }

        for (int e = 0; e < n; ++e)
        {
            if (dist[e] != g[s][e])
            {
                return false;
            }
        }

        return true;
    };

    for (int i = 0; i < n; ++i)
    {
        if (!bfs(i))
        {
            std::cout << "No\n";
            return;
        }
    }

    std::cout << "Yes\n";
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
