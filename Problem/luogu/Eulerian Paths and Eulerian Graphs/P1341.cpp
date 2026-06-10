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
    int n;
    std::cin >> n;

    std::vector<std::string> cs(n);
    for (auto &s: cs)
    {
        std::cin >> s;
    }

    auto cd = [&](char c) -> int
    {
        if (c >= 'A' && c <= 'Z')
        {
            return c - 'A';
        }

        return 26 + c - 'a';
    };

    auto cc = [&](int x) -> char
    {
        if (x >= 0 && x <= 25)
        {
            return x + 'A';
        }

        return x - 26 + 'a';
    };

    std::vector<std::vector<int>> g(52);
    for (auto &s: cs)
    {
        int u = cd(s[0]), v = cd(s[1]);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::vector<int> head(52, -1), next(2 * n, -1), to(2 * n, -1);
    int cnt = 0;

    auto add_edge = [&](int u, int v) -> void
    {
        next[cnt] = head[u];
        to[cnt] = v;
        head[u] = cnt++;
    };

    std::vector<int> degree(52);
    for (int u = 51; u >= 0; --u)
    {
        ranges::sort(g[u]);
        for (int i = std::ssize(g[u]) - 1; i >= 0; --i)
        {
            int v = g[u][i];
            if (u < v)
            {
                ++degree[u], ++degree[v];
                add_edge(u, v);
                add_edge(v, u);
            }
            else if (u == v)
            {
                ++degree[u];
                add_edge(u, u);
            }
        }
    }

    auto start = [&]() -> std::optional<int>
    {
        int odd = 0;
        for (int i = 0; i < 52; ++i)
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

        for (int i = 0; i < 52; ++i)
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
        std::cout << "No Solution\n";
        return;
    }

    std::vector<bool> visited(n);
    std::string path;
    auto cur = head;

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

        path += cc(u);
    } (*start);

    if (std::ssize(path) != n + 1)
    {
        std::cout << "No Solution\n";
        return;
    }

    ranges::reverse(path);

    std::cout << path << "\n";
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
