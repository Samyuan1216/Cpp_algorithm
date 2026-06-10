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
    int m;
    std::cin >> m;

    std::vector<std::vector<int>> g(500);
    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::vector<int> head(500, -1), next(2 * m), to(2 * m);
    int cnt = 0;

    auto add_edge = [&](int u, int v) -> void
    {
        next[cnt] = head[u];
        to[cnt] = v;
        head[u] = cnt++;
    };

    std::vector<int> degree(500);
    for (int u = 499; u >= 0; --u)
    {
        ranges::sort(g[u]);
        for (int i = std::ssize(g[u]) - 1; i >= 0; --i)
        {
            int v = g[u][i];
            if (u < v)
            {
                ++degree[u], ++degree[v];
                add_edge(u, v), add_edge(v, u);
            }
        }
    }

    auto start = [&]() -> std::optional<int>
    {
        int odd = 0;
        for (int i = 0; i < 500; ++i)
        {
            if (degree[i] & 1)
            {
                ++odd;
            }
        }

        if (odd != 0 && odd != 2)
        {
            return std::nullopt;
        }

        for (int i = 0; i < 500; ++i)
        {
            if (odd == 0 && degree[i] > 0)
            {
                return i;
            }

            if (odd == 2 && (degree[i] & 1))
            {
                return i;
            }
        }

        return std::nullopt;
    } ();

    if (!start)
    {
        std::cout << "No\n";
        return;
    }

    std::vector<int> cur = head, path;
    std::vector<bool> visited(m);

    [&](this auto &&dfs, int u) -> void
    {
        for (int ei = cur[u]; ei != -1; ei = cur[u])
        {
            cur[u] = next[ei];
            if (visited[ei >> 1])
            {
                continue;
            }

            visited[ei >> 1] = true;
            dfs(to[ei]);
        }

        path.push_back(u);
    } (*start);

    if (std::ssize(path) != m + 1)
    {
        std::cout << "No\n";
        return;
    }

    ranges::reverse(path);
    for (auto &x: path)
    {
        std::cout << x + 1 << "\n";
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
