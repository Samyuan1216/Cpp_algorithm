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

    std::vector<int> c(n);
    for (auto &x: c)
    {
        std::cin >> x;
    }

    std::vector<std::vector<int>> g(n);
    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::vector<int> father(n), size(n, 1), son(n, -1);
    [&](this auto &&dfs, int u, int f) -> void
    {
        father[u] = f;
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
    } (0, 0);

    std::vector<int> cnt(n + 1);
    int max = 0;
    i64 sum = 0;

    auto effect = [&](this auto &&dfs, int u) -> void
    {
        if (++cnt[c[u]] > max)
        {
            max = cnt[c[u]];
            sum = c[u];
        }
        else if (cnt[c[u]] == max)
        {
            sum += c[u];
        }

        for (auto &v: g[u])
        {
            if (v == father[u])
            {
                continue;
            }

            dfs(v);
        }
    };

    auto cancel = [&](this auto &&dfs, int u) -> void
    {
        cnt[c[u]] = max = sum = 0;
        for (auto &v: g[u])
        {
            if (v == father[u])
            {
                continue;
            }

            dfs(v);
        }
    };

    std::vector<i64> ans(n);
    [&](this auto &&dfs, int u, int keep) -> void
    {
        for (auto &v: g[u])
        {
            if (v == father[u] || v == son[u])
            {
                continue;
            }

            dfs(v, 0);
        }

        if (son[u] != -1)
        {
            dfs(son[u], 1);
        }

        for (auto &v: g[u])
        {
            if (v == father[u] || v == son[u])
            {
                continue;
            }

            effect(v);
        }

        if (++cnt[c[u]] > max)
        {
            max = cnt[c[u]];
            sum = c[u];
        }
        else if (cnt[c[u]] == max)
        {
            sum += c[u];
        }

        ans[u] = sum;
        if (keep == 0)
        {
            cancel(u);
        }
    } (0, 0);

    for (int i = 0; i < n; ++i)
    {
        std::cout << ans[i] << " \n"[i == n - 1];
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
