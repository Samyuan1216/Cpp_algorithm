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

    std::vector<int> head(n, -1), to(m << 1), next(m << 1);
    int cntg = 0;

    auto add_edge = [&](int u, int v) -> void
    {
        next[cntg] = head[u];
        to[cntg] = v;
        head[u] = cntg++;
    };

    std::set<std::array<int, 2>> s;
    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        if (s.contains({std::min(u, v), std::max(u, v)}))
        {
            continue;
        }

        add_edge(u, v);
        add_edge(v, u);

        s.insert({std::min(u, v), std::max(u, v)});
    }

    std::vector<int> dfn(n, -1), low(n), belong(n);
    std::stack<int> sta;
    int cntd = 0, ebcc = 0;

    [&](this auto &&self, int u, int pre) -> void
    {
        dfn[u] = low[u] = cntd++;
        sta.push(u);

        for (int ei = head[u], v; ei != -1; ei = next[ei])
        {
            if ((ei ^ 1) == pre)
            {
                continue;
            }

            v = to[ei];
            if (dfn[v] == -1)
            {
                self(v, ei);

                low[u] = std::min(low[u], low[v]);
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
    } (0, -1);

    std::vector<std::vector<int>> g(ebcc);
    for (int u = 0; u < n; ++u)
    {
        for (int ei = head[u], v; ei != -1; ei = next[ei])
        {
            v = to[ei];
            if (belong[u] == belong[v])
            {
                continue;
            }

            g[belong[u]].push_back(belong[v]);
        }
    }

    std::vector<int> father(n, -1), deep(n), size(n, 1), son(n, -1);
    [&](this auto &&self, int u, int f) -> void
    {
        father[u] = f;
        deep[u] = deep[f] + 1;

        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            self(v, u);

            size[u] += size[v];
            if (son[u] == -1 || size[son[u]] < size[v])
            {
                son[u] = v;
            }
        }
    } (0, 0);

    std::vector<int> top(n);
    [&](this auto &&self, int u, int t) -> void
    {
        top[u] = t;
        if (son[u] == -1)
        {
            return;
        }

        self(son[u], t);
        for (auto &v: g[u])
        {
            if (v == father[u] || v == son[u])
            {
                continue;
            }

            self(v, v);
        }
    } (0, 0);

    auto lca = [&](int a, int b) -> int
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
    };

    int q;
    std::cin >> q;

    while (q--)
    {
        int a, b;
        std::cin >> a >> b;
        --a, --b;

        std::cout << std::format("{:b}\n", deep[belong[a]] + deep[belong[b]] - 2 * deep[lca(belong[a], belong[b])] + 1);
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
