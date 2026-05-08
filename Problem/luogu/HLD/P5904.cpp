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

    std::vector<std::vector<int>> grid(n);
    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        grid[u].push_back(v);
        grid[v].push_back(u);
    }

    std::vector<int> father(n, -1), length(n), son(n, -1);
    [&](this auto &&dfs, int u, int f) -> void
    {
        father[u] = f;
        for (auto &v: grid[u])
        {
            if (v == f)
            {
                continue;
            }

            dfs(v, u);

            if (son[u] == -1 || length[son[u]] < length[v])
            {
                son[u] = v;
            }
        }

        length[u] = (son[u] == -1? 0: length[son[u]]) + 1;
    } (0, -1);

    std::vector<int> fid(n), gid(n);
    int cnt = 0;

    [&](this auto &&dfs, int u, int t) -> void
    {
        fid[u] = cnt++;
        if (son[u] == -1)
        {
            gid[u] = fid[t] * 2;

            return;
        }

        dfs(son[u], t);
        for (auto &v: grid[u])
        {
            if (v == father[u] || v == son[u])
            {
                continue;
            }

            dfs(v, v);
        }

        gid[u] = gid[son[u]] + 1;
    } (0, 0);

    std::vector<i64> f(n), g(n << 1);
    i64 ans = 0;

    [&](this auto &&dfs, int u) -> void
    {
        f[fid[u]] = 1;
        if (son[u] == -1)
        {
            return;
        }

        dfs(son[u]);
        for (auto &v: grid[u])
        {
            if (v == father[u] || v == son[u])
            {
                continue;
            }

            dfs(v);

            for (int i = 0; i <= length[v]; ++i)
            {
                if (i < length[u] && i - 1 >= 0)
                {
                    ans += g[gid[u] + i] * f[fid[v] + i - 1];
                }

                if (i > 0 && i + 1 < length[v])
                {
                    ans += f[fid[u] + i] * g[gid[v] + i + 1];
                }
            }

            for (int i = 0; i <= length[v]; ++i)
            {
                if (i + 1 < length[v])
                {
                    g[gid[u] + i] += g[gid[v] + i + 1];
                }

                if (i - 1 >= 0)
                {
                    g[gid[u] + i] += f[fid[u] + i] * f[fid[v] + i - 1];
                }
            }

            for (int i = 0; i <= length[v]; ++i)
            {
                if (i - 1 >= 0)
                {
                    f[fid[u] + i] += f[fid[v] + i - 1];
                }
            }
        }

        ans += g[gid[u]];
    } (0);

    std::cout << ans << "\n";
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
