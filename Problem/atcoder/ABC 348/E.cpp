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

    std::vector<i64> w(n);
    for (auto &x: w)
    {
        std::cin >> x;
    }

    std::vector<i64> sum(n);
    i64 sum0 = 0;

    [&](this auto &&dfs, int u, int f, int level) -> void
    {
        sum[u] = w[u];
        sum0 += w[u] * level;

        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            dfs(v, u, level + 1);
            sum[u] += sum[v];
        }
    } (0, -1, 0);

    i64 ans = sum0;
    [&](this auto &&dfs, int u, int f, i64 val) -> void
    {
        ans = std::min(ans, val);
        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            dfs(v, u, val - sum[v] + (sum[0] - sum[v]));
        }
    } (0, -1, sum0);

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
