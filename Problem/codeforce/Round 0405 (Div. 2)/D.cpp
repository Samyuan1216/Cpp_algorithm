#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

template<typename T>
using lim = std::numeric_limits<T>;

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
    i64 n, k;
    std::cin >> n >> k;

    std::vector<std::vector<int>> g(n);
    for (int i = 0, u, v; i < n - 1; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::vector<int> size(n);
    std::vector<i64> cnt(k);
    auto dp = std::vector(n, std::vector<i64>(k));
    i64 sum_L = 0;

    [&](this auto &&dfs, int u, int f) -> void
    {
        size[u] = 1;
        dp[u][0] = 1;

        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            dfs(v, u);

            sum_L += i64(size[v]) * (n - size[v]);
            for (int x = 0; x < k; ++x)
            {
                for (int y = 0; y < k; ++y)
                {
                    cnt[(x + y + 1) % k] += dp[u][x] * dp[v][y];
                }
            }

            for (int y = 0; y < k; ++y)
            {
                dp[u][(y + 1) % k] += dp[v][y];
            }

            size[u] += size[v];
        }
    } (0, 0);

    i64 sum_f = 0;
    for (int i = 1; i < k; ++i)
    {
        sum_f += cnt[i] * (k - i);
    }

    i64 ans = (sum_L + sum_f) / k;
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
