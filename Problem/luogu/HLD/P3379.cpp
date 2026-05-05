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
    int n, m, s;
    std::cin >> n >> m >> s;
    --s;

    std::vector<std::vector<int>> g(n);
    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::vector<int> father(n, -1), deep(n), size(n), son(n, -1);
    [&](this auto &&dfs, int u, int f) -> void
    {
        father[u] = f;
        deep[u] = (f == -1? 0: deep[f]) + 1;
        size[u] = 1;

        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            dfs(v, u);

            size[u] += size[v];
            if (son[u] == -1 || size[son[u]] < size[v])
            {
                son[u] = v;
            }
        }
    } (s, -1);

    std::vector<int> top(n);
    [&](this auto &&dfs, int u, int t) -> void
    {
        top[u] = t;
        if (son[u] == -1)
        {
            return;
        }

        dfs(son[u], t);
        for (auto &v: g[u])
        {
            if (v == father[u] || v == son[u])
            {
                continue;
            }

            dfs(v, v);
        }
    } (s, s);

    auto lca = [&](int a, int b) -> int
    {
        while (top[a] != top[b])
        {
            if (deep[top[a]] <= deep[top[b]])
            {
                b = father[top[b]];
            }
            else
            {
                a = father[top[a]];
            }
        }

        return (deep[a] <= deep[b]? a: b);
    };

    while (m--)
    {
        int a, b;
        std::cin >> a >> b;
        --a, --b;

        std::cout << lca(a, b) + 1 << "\n";
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
