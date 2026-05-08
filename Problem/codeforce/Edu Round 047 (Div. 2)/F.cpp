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
    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::vector<int> length(n), son(n, -1);
    [&](this auto &&dfs, int u, int f) -> void
    {
        for (auto &v: g[u])
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

    std::vector<int> dfn(n), dp(n), ans(n);
    int cnt = 0;

    [&](this auto &&dfs, int u, int f) -> void
    {
        dfn[u] = cnt++;
        dp[dfn[u]] = 1;

        if (son[u] == -1)
        {
            return;
        }

        dfs(son[u], u);
        for (auto &v: g[u])
        {
            if (v == f || v == son[u])
            {
                continue;
            }

            dfs(v, u);
        }

        ans[u] = ans[son[u]] + 1;
        for (auto &v: g[u])
        {
            if (v == f || v == son[u])
            {
                continue;
            }

            for (int i = 1; i <= length[v]; ++i)
            {
                dp[dfn[u] + i] += dp[dfn[v] + i - 1];
                if (dp[dfn[u] + i] > dp[dfn[u] + ans[u]] || ((dp[dfn[u] + i] == dp[dfn[u] + ans[u]]) && i < ans[u]))
                {
                    ans[u] = i;
                }
            }
        }

        if (dp[dfn[u] + ans[u]] == 1)
        {
            ans[u] = 0;
        }
    } (0, -1);

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
