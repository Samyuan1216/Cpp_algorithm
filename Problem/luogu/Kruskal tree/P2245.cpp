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

    std::vector<std::array<int, 3>> edges(m);
    for (auto &[w, u, v]: edges)
    {
        std::cin >> u >> v >> w;
        --u, --v;
    }

    ranges::sort(edges);

    std::vector<int> father(n);
    ranges::iota(father, 0);

    auto find = [&](this auto &&find, int i) -> int
    {
        return (father[i] = (father[i] == i? i: find(father[i])));
    };

    std::vector<std::vector<int>> g(n);
    std::vector<int> w(n);

    for (int i = 0; i < m; ++i)
    {
        if (int fx = find(edges[i][1]), fy = find(edges[i][2]); fx != fy)
        {
            father[fx] = father[fy] = std::ssize(father);
            father.push_back(std::ssize(father));
            w.push_back(edges[i][0]);

            g.push_back({});
            g.back().push_back(fx);
            g.back().push_back(fy);
        }
    }

    constexpr int limit = 20;
    std::vector<int> deep(std::ssize(father));
    auto stjump = std::vector(std::ssize(father), std::vector<int>(limit));

    for (int i = 0; i < std::ssize(father); ++i)
    {
        if (i != father[i])
        {
            continue;
        }

        [&](this auto &&dfs, int u, int f) -> void
        {
            deep[u] = deep[f] + 1;
            stjump[u][0] = f;

            for (int p = 1; p < limit; ++p)
            {
                stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
            }

            for (auto &v: g[u])
            {
                dfs(v, u);
            }
        } (i, i);
    }

    int q;
    std::cin >> q;

    auto lca = [&](int a, int b)
    {
        if (deep[a] < deep[b])
        {
            std::swap(a, b);
        }

        for (int p = limit - 1; p >= 0; --p)
        {
            if (deep[stjump[a][p]] >= deep[b])
            {
                a = stjump[a][p];
            }
        }

        if (a == b)
        {
            return a;
        }

        for (int p = limit - 1; p >= 0; --p)
        {
            if (stjump[a][p] != stjump[b][p])
            {
                a = stjump[a][p];
                b = stjump[b][p];
            }
        }

        return stjump[a][0];
    };

    while (q--)
    {
        int x, y;
        std::cin >> x >> y;
        --x, --y;

        if (find(x) != find(y))
        {
            std::cout << "impossible\n";
        }
        else
        {
            std::cout << w[lca(x, y)] << "\n";
        }
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
