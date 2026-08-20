// https://acm.hdu.edu.cn/showproblem.php?pid=2460

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

void solve(int n, int m)
{
    std::vector<int> head(n, -1), next(m << 1), to(m << 1);
    int cntg = 0;

    auto add_edge = [&](int u, int v) -> void
    {
        next[cntg] = head[u];
        to[cntg] = v;
        head[u] = cntg++;
    };

    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        add_edge(u, v);
        add_edge(v, u);
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

    std::vector<int> parent(ebcc), deep(ebcc);
    [&](this auto &&self, int u, int f) -> void
    {
        parent[u] = f;
        deep[u] = deep[f] + 1;

        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            self(v, u);
        }
    } (0, 0);

    std::vector<int> father(ebcc);
    ranges::iota(father, 0);

    auto find = [&](this auto &&self, int i) -> int
    {
        return father[i] = (father[i] == i? i: self(father[i]));
    };

    auto merge = [&](int x, int y) -> void
    {
        x = find(x), y = find(y);
        if (x == y)
        {
            return;
        }

        if (deep[x] < deep[y])
        {
            father[y] = x;
        }
        else
        {
            father[x] = y;
        }
    };

    int q;
    std::cin >> q;

    while (q--)
    {
        int a, b;
        std::cin >> a >> b;
        --a, --b;

        a = find(belong[a]), b = find(belong[b]);
        while (a != b)
        {
            if (deep[a] >= deep[b])
            {
                merge(a, parent[a]);
                a = find(a);
            }
            else
            {
                merge(b, parent[b]);
                b = find(b);
            }

            --ebcc;
        }

        std::cout << ebcc - 1 << "\n";
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    for (int t = 1; ; ++t)
    {
        int n, m;
        std::cin >> n >> m;

        if (n == 0 && m == 0)
        {
            break;
        }

        std::cout << std::format("Case {}:\n", t);
        solve(n, m);
        std::cout << "\n";
    }
}
