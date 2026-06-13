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

    std::vector<std::tuple<i64, int, int, int>> edges(m);
    for (int i = 0; auto &[w, u, v, id]: edges)
    {
        std::cin >> u >> v >> w;
        --u, --v;

        id = i++;
    }

    ranges::sort(edges);

    std::vector<int> father(n), size(n, 1);
    ranges::iota(father, 0);

    auto find = [&](this auto &&find, int i) -> int
    {
        father[i] = (father[i] == i? i: find(father[i]));
        return father[i];
    };

    auto merge = [&](int u, int v) -> bool
    {
        if (int uf = find(u), vf = find(v); uf != vf)
        {
            if (size[uf] < size[vf])
            {
                std::swap(uf, vf);
            }

            father[vf] = uf;
            size[uf] += size[vf];

            return true;
        }

        return false;
    };

    std::vector<std::vector<std::tuple<int, i64, int>>> g(n);
    std::vector<bool> in_tree(m);

    i64 weight = 0;
    for (auto &[w, u, v, id]: edges)
    {
        if (merge(u, v))
        {
            g[u].push_back({v, w, id});
            g[v].push_back({u, w, id});

            in_tree[id] = true;
            weight += w;
        }
    }

    constexpr int limit = 20;
    auto stjump = std::vector(n, std::vector<int>(limit));
    auto stmax = std::vector(n, std::vector<i64>(limit));
    std::vector<int> deep(n);

    [&](this auto &&dfs, int u, int f, i64 w) -> void
    {
        stjump[u][0] = f, stmax[u][0] = w;
        deep[u] = deep[f] + 1;

        for (int p = 1; p < limit; ++p)
        {
            stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
            stmax[u][p] = std::max(stmax[u][p - 1], stmax[stjump[u][p - 1]][p - 1]);
        }

        for (auto &[v, vw, id]: g[u])
        {
            if (v == f)
            {
                continue;
            }

            dfs(v, u, vw);
        }
    } (0, 0, 0);

    auto query = [&](int u, int v) -> i64
    {
        i64 w = 0;
        if (deep[u] < deep[v])
        {
            std::swap(u, v);
        }

        for (int p = limit - 1; p >= 0; --p)
        {
            if (deep[stjump[u][p]] >= deep[v])
            {
                w = std::max(w, stmax[u][p]);
                u = stjump[u][p];
            }
        }

        if (u == v)
        {
            return w;
        }

        for (int p = limit - 1; p >= 0; --p)
        {
            if (stjump[u][p] != stjump[v][p])
            {
                w = std::max({w, stmax[u][p], stmax[v][p]});
                u = stjump[u][p], v = stjump[v][p];
            }
        }

        return std::max({w, stmax[u][0], stmax[v][0]});
    };

    std::vector<i64> ans(m);
    for (auto &[w, u, v, id]: edges)
    {
        if (in_tree[id])
        {
            ans[id] = weight;
        }
        else
        {
            ans[id] = weight - query(u, v) + w;
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
