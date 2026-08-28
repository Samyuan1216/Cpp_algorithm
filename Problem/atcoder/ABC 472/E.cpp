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
    std::vector<std::array<int, 2>> edges(m);

    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        edges[i] = {u, v};
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }

    std::vector<int> deep(n), father(n);
    std::vector<bool> vis1(n), vis2(m);

    [&](this auto &&self, int u, int f) -> void
    {
        deep[u] = deep[f] + 1;
        father[u] = f;
        vis1[u] = true;

        for (auto &[v, id]: g[u])
        {
            if (v == f || vis1[v])
            {
                continue;
            }

            vis2[id] = true;
            self(v, u);
        }
    } (0, 0);

    for (int i = 0, u, v; i < m; ++i)
    {
        u = edges[i][0], v = edges[i][1];
        if (vis2[i] || (std::abs(deep[u] - deep[v]) + 1) % 2 == 0)
        {
            continue;
        }

        std::vector<int> p1, p2;
        if (deep[u] < deep[v])
        {
            std::swap(u, v);
        }

        while (deep[u] != deep[v])
        {
            p1.push_back(u);
            u = father[u];
        }

        while (u != v)
        {
            p1.push_back(u);
            p2.push_back(v);

            u = father[u], v = father[v];
        }

        std::cout << std::ssize(p1) + std::ssize(p2) + 1 << "\n";
        std::cout << u + 1;

        ranges::reverse(p1);
        for (auto &x: p1)
        {
            std::cout << " " << x + 1;
        }

        for (auto &x: p2)
        {
            std::cout << " " << x + 1;
        }
        std::cout << "\n";

        return;
    }

    std::cout << -1 << "\n";
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
