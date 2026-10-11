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

struct EBCC
{
    const std::vector<std::vector<std::array<int, 2>>> &g;
    std::vector<int> dfn, low, belong;
    std::vector<bool> cut;
    std::stack<int> sta;
    int cnt = 0, ebcc = 0;

    EBCC(const std::vector<std::vector<std::array<int, 2>>> &adj, int m): g(adj), dfn(std::ssize(adj), -1), low(std::ssize(adj)), belong(std::ssize(adj)), cut(m)
    {
        for (int i = 0; i < std::ssize(g); ++i)
        {
            if (dfn[i] != -1)
            {
                continue;
            }

            dfs(i, -1);
        }
    }

    void dfs(int u, int pre)
    {
        dfn[u] = low[u] = cnt++;
        sta.push(u);

        for (auto &[v, id]: g[u])
        {
            if (id == pre)
            {
                continue;
            }

            if (dfn[v] == -1)
            {
                dfs(v, id);

                low[u] = std::min(low[u], low[v]);
                if (low[v] > dfn[u])
                {
                    cut[id] = true;
                }
            }
            else
            {
                low[u] = std::min(low[u], dfn[v]);
            }
        }

        if (int t; dfn[u] == low[u])
        {
            do
            {
                t = sta.top();
                sta.pop();

                belong[t] = ebcc;
            } while (t != u);

            ++ebcc;
        }
    }
    
    std::vector<std::vector<int>> get() const
    {
        std::vector<std::vector<int>> res(ebcc);
        for (int i = 0; i < std::ssize(g); ++i)
        {
            res[belong[i]].push_back(i);
        }

        return res;
    }
};

struct HLD
{
    const std::vector<std::vector<int>> &g;
    std::vector<int> father, deep, size, son, top, dfn, seg, block;
    int cnt = 0, n;

    HLD(const std::vector<std::vector<int>> &adj): g(adj), father(std::ssize(adj), -1), deep(std::ssize(adj)), size(std::ssize(adj), 1), son(std::ssize(adj), -1), top(std::ssize(adj)), dfn(std::ssize(adj)), seg(std::ssize(adj)), block(std::ssize(adj)), n(std::ssize(adj))
    {
        for (int i = 0, j = 0; i < n; ++i)
        {
            if (father[i] != -1)
            {
                continue;
            }

            block[i] = j++;

            dfs1(i, i);
            dfs2(i, i);
        }
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

            block[v] = block[u];
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

void solve()
{
    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<std::vector<std::array<int, 2>>> g1(n);
    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g1[u].push_back({v, i});
        g1[v].push_back({u, i});
    }

    EBCC ebcc(g1, m);

    std::vector<std::vector<int>> g2(ebcc.ebcc);
    for (int u = 0; u < n; ++u)
    {
        for (auto &[v, id]: g1[u])
        {
            if (ebcc.belong[u] == ebcc.belong[v])
            {
                continue;
            }

            g2[ebcc.belong[u]].push_back(ebcc.belong[v]);
        }
    }

    HLD hld(g2);

    std::vector<int> up(ebcc.ebcc), down(ebcc.ebcc);
    while (q--)
    {
        int s, d;
        std::cin >> s >> d;
        --s, --d;

        if (hld.block[ebcc.belong[s]] != hld.block[ebcc.belong[d]])
        {
            std::cout << "No\n";
            return;
        }

        if (ebcc.belong[s] == ebcc.belong[d])
        {
            continue;
        }

        int l = hld.lca(ebcc.belong[s], ebcc.belong[d]);
        ++up[ebcc.belong[s]], --up[l];
        ++down[ebcc.belong[d]], --down[l];
    }

    std::vector<bool> vis(ebcc.ebcc);
    for (int i = 0; i < ebcc.ebcc; ++i)
    {
        if (vis[i])
        {
            continue;
        }

        bool status = [&](this auto &&self, int u, int f) -> bool
        {
            vis[u] = true;
            for (auto &v: g2[u])
            {
                if (v == f)
                {
                    continue;
                }

                if (!self(v, u))
                {
                    return false;
                }

                up[u] += up[v];
                down[u] += down[v];
            }

            return up[u] == 0 || down[u] == 0;
        } (i, i);

        if (!status)
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
