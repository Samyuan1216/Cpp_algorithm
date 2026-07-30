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

    std::vector<std::vector<int>> g(n);
    std::vector<int> root;

    for (int i = 0, p; i < n; ++i)
    {
        std::cin >> p;
        --p;

        if (p == -1)
        {
            root.push_back(i);
        }
        else
        {
            g[p].push_back(i);
        }
    }

    int m;
    std::cin >> m;

    std::vector<std::vector<std::array<int, 2>>> q1(n);
    for (int id = 0, v, p; id < m; ++id)
    {
        std::cin >> v >> p;
        --v;

        q1[v].push_back({p, id});
    }

    std::vector<int> ans(m), size(n, 1), son(n, -1), deep(n);
    std::vector<std::vector<std::array<int, 2>>> q2(n);
    auto stjump = std::vector(n, std::vector<int>(30));

    for (auto &s: root)
    {
        auto get_kth = [&](int u, int k)
        {
            for (int p = 29; p >= 0; --p)
            {
                if ((k >> p) & 1)
                {
                    u = stjump[u][p];
                }
            }

            return u;
        };

        int depth = 0;
        [&](this auto &&dfs, int u, int f, int d) -> void
        {
            deep[u] = d;

            stjump[u][0] = f;
            for (int p = 1; p < 30; ++p)
            {
                stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
            }

            for (auto &[p, id]: q1[u])
            {
                if (deep[u] >= p)
                {
                    int v = get_kth(u, p);
                    q2[v].push_back({deep[u], id});
                }
            }

            depth = std::max(depth, d);
            for (auto &v: g[u])
            {
                dfs(v, u, d + 1);

                size[u] += size[v];
                if (son[u] == -1 || size[son[u]] < size[v])
                {
                    son[u] = v;
                }
            }
        } (s, s, 0);


        std::vector<int> cnt(depth + 1);
        auto effect = [&](this auto &&dfs, int u, int d) -> void
        {
            ++cnt[d];
            for (auto &v: g[u])
            {
                dfs(v, d + 1);
            }
        };

        auto cancel = [&](this auto &&dfs, int u, int d) -> void
        {
            cnt[d] = 0;
            for (auto &v: g[u])
            {
                dfs(v, d + 1);
            }
        };

        [&](this auto &&dfs, int u, int d, int keep) -> void
        {
            for (auto &v: g[u])
            {
                if (v == son[u])
                {
                    continue;
                }

                dfs(v, d + 1, 0);
            }

            if (son[u] != -1)
            {
                dfs(son[u], d + 1, 1);
            }

            for (auto &v: g[u])
            {
                if (v == son[u])
                {
                    continue;
                }

                effect(v, d + 1);
            }

            ++cnt[d];
            for (auto &[td, id]: q2[u])
            {
                ans[id] = cnt[td] - 1;
            }

            if (keep == 0)
            {
                cancel(u, d);
            }
        } (s, 0, 0);
    }

    for (int i = 0; i < m; ++i)
    {
        std::cout << ans[i] << " \n"[i == m - 1];
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
