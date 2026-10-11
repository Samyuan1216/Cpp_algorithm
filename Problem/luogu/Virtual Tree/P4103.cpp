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

struct HLD
{
    const std::vector<std::vector<int>> &g;
    std::vector<int> father, deep, size, son, top, dfn, seg;
    int cnt = 0, n;

    HLD(const std::vector<std::vector<int>> &adj, int root = 0): g(adj), father(std::ssize(adj), -1), deep(std::ssize(adj)), size(std::ssize(adj), 1), son(std::ssize(adj), -1), top(std::ssize(adj)), dfn(std::ssize(adj)), seg(std::ssize(adj)), n(std::ssize(adj))
    {
        dfs1(root, root);
        dfs2(root, root);
    }

    void dfs1(int u, int f)
    {
        father[u] = f;
        deep[u] = deep[f] + 1;

        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            dfs1(v, u);

            size[u] += size[v];
            if (son[u] == -1 || size[son[u]] < size[v])
            {
                son[u] = v;
            }
        }
    }

    void dfs2(int u, int t)
    {
        top[u] = t;
        dfn[u] = cnt;
        seg[cnt++] = u;

        if (son[u] == -1)
        {
            return;
        }

        dfs2(son[u], t);
        for (auto &v: g[u])
        {
            if (v == father[u] || v == son[u])
            {
                continue;
            }

            dfs2(v, v);
        }
    }

    int lca(int a, int b)
    {
        while (top[a] != top[b])
        {
            if (deep[top[a]] > deep[top[b]])
            {
                a = father[top[a]];
            }
            else
            {
                b = father[top[b]];
            }
        }

        return (deep[a] <= deep[b]? a: b);
    }

    int dist(int x, int y)
    {
        return deep[x] + deep[y] - 2 * deep[lca(x, y)];
    }

    int intersection(int x1, int y1, int x2, int y2)
    {
        std::vector<int> t = {lca(x1, x2), lca(x1, y2), lca(y1, x2), lca(y1, y2)};
        ranges::sort(t, {}, [&](int x) { return deep[x]; });

        int r1 = lca(x1, y1), r2 = lca(x2, y2);
        if (deep[t[0]] < std::min(deep[r1], deep[r2]) || deep[t[2]] < std::max(deep[r1], deep[r2]))
        {
            return 0;
        }

        return dist(t[2], t[3]) + 1;
    }

    void modify(auto &tr, int x, int y, auto &z)
    {
        while (top[x] != top[y])
        {
            if (deep[top[x]] > deep[top[y]])
            {
                tr.modify(dfn[top[x]], dfn[x], z);
                x = father[top[x]];
            }
            else
            {
                tr.modify(dfn[top[y]], dfn[y], z);
                y = father[top[y]];
            }
        }

        tr.modify(std::min(dfn[x], dfn[y]), std::max(dfn[x], dfn[y]), z);
    }

    auto query(auto &tr, int x, int y)
    {
        i64 ans = -1e18;
        while (top[x] != top[y])
        {
            if (deep[top[x]] > deep[top[y]])
            {
                ans = std::max(ans, tr.query(dfn[top[x]], dfn[x]).max);
                x = father[top[x]];
            }
            else
            {
                ans = std::max(ans, tr.query(dfn[top[y]], dfn[y]).max);
                y = father[top[y]];
            }
        }

        return std::max(ans, tr.query(std::min(dfn[x], dfn[y]), std::max(dfn[x], dfn[y])).max);
    }
};

struct Virtual_Tree
{
    HLD hld;
    std::vector<std::vector<int>> g;
    std::vector<int> tmp;
    int root = -1;

    Virtual_Tree(const std::vector<std::vector<int>> &adj, int root = 0): hld(adj, root), g(std::ssize(adj)) {}

    void build(std::vector<int> arr)
    {
        for (auto &x: tmp)
        {
            g[x].clear();
        }
        tmp.clear();

        if (arr.empty())
        {
            root = -1;
            return;
        }

        ranges::sort(arr, {}, [&](int x) { return hld.dfn[x]; });

        for (int i = 0; i < std::ssize(arr) - 1; ++i)
        {
            tmp.push_back(arr[i]);
            tmp.push_back(hld.lca(arr[i], arr[i + 1]));
        }
        tmp.push_back(arr.back());

        ranges::sort(tmp, {}, [&](int x) { return hld.dfn[x]; });
        auto [l, r] = ranges::unique(tmp);
        tmp.erase(l, r);

        for (int i = 0, u, v; i < std::ssize(tmp) - 1; ++i)
        {
            u = hld.lca(tmp[i], tmp[i + 1]),  v = tmp[i + 1];
            g[u].push_back(v);
        }

        root = tmp[0];
    }
};

void solve()
{
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> g(n);
    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    Virtual_Tree vir(g);

    int q;
    std::cin >> q;

    constexpr i64 INF = 1e18;
    std::vector<i64> size(n), sum(n), near(n), far(n);
    std::vector<bool> key(n);

    while (q--)
    {
        int k;
        std::cin >> k;

        std::vector<int> arr(k);
        for (auto &x: arr)
        {
            std::cin >> x;
            --x;

            key[x] = true;
        }

        vir.build(arr);

        i64 total_sum = 0, total_min = INF, total_max = -INF;
        [&](this auto &&self, int u) -> void
        {
            sum[u] = 0;
            size[u] = (key[u]? 1: 0);

            if (key[u])
            {
                near[u] = far[u] = 0;
            }
            else
            {
                near[u] = INF, far[u] = -INF;
            }

            for (auto &v: vir.g[u])
            {
                self(v);

                i64 len = vir.hld.deep[v] - vir.hld.deep[u];
                total_sum += (sum[u] + size[u] * len) * size[v] + sum[v] * size[u];

                size[u] += size[v];
                sum[u] += sum[v] + len * size[v];

                total_min = std::min(total_min, near[u] + near[v] + len);
                total_max = std::max(total_max, far[u] + far[v] + len);

                near[u] = std::min(near[u], near[v] + len);
                far[u] = std::max(far[u], far[v] + len);
            }
        } (vir.root);

        std::cout << total_sum << " " << total_min << " " << total_max << "\n";

        for (auto &x: arr)
        {
            key[x] = false;
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
