#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = int64_t;

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
    constexpr int N = 1010;
    int n;
    std::cin >> n;

    auto w = std::vector<int>(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> w[i];
    }

    auto g = std::vector(n + 1, std::vector<int>());
    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    auto dp = std::vector(n + 1, std::bitset<N>());
    auto dfs = [&](auto &&self, int u, int f) -> void
    {
        if (g[u].size() == 1 && f != 0)
        {
            dp[u][0] = 1;
            if (w[u] < N)
            {
                dp[u][w[u]] = 1;
            }

            return;
        }

        std::bitset<N> cur, mask;
        cur[0] = 1;

        for (int i = 0; i <= w[u]; ++i)
        {
            mask[i] = 1;
        }

        for (auto &v: g[u])
        {
            if (v != f)
            {
                self(self, v, u);

                std::bitset<N> next;
                next[0] = 1;

                for (int s = cur._Find_first(); s <= w[u]; s = cur._Find_next(s))
                {
                    next |= (dp[v] << s);
                }

                next &= mask;
                cur = next;
            }
        }

        dp[u] = cur;
    };

    dfs(dfs, 1, 0);

    int ans = 0;
    for (int x = w[1]; x >= 0; --x)
    {
        if (dp[1][x] == 1)
        {
            ans = x;
            break;
        }
    }

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
