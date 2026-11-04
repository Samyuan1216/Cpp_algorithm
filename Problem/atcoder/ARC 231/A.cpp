#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

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
    constexpr i64 INF = 1e18;
    std::vector dp(500, std::vector<i64>(500, INF));

    for (int y = 0; y < 500; ++y)
    {
        dp[0][y] = 1ll * y * y;
    }

    int n;
    std::cin >> n;

    i64 best = 0, sum = 0;
    for (int i = 0, ex, ey, ez; i < n; ++i)
    {
        std::cin >> ex >> ey >> ez;

        i64 v = INF;
        for (int x = 0; x < 500; ++x)
        {
            if (dp[x][ey] == INF)
            {
                continue;
            }

            v = std::min(v, dp[x][ey] + 1ll * (x - ex) * (x - ex));
        }

        v -= ez;
        best = std::min(best, v);

        for (int y = 0; y < 500; ++y)
        {
            dp[ex][y] = std::min(dp[ex][y], v + 1ll * (y - ey) * (y - ey));
        }

        sum += ez;
    }

    std::cout << sum + best << "\n";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    std::cin >> t;
    while (t--)
    {
        solve();
    }
}