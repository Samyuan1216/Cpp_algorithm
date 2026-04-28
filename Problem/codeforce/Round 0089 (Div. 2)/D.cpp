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
    constexpr i64 mod = 100000000;

    int n1, n2, k1, k2;
    std::cin >> n1 >> n2 >> k1 >> k2;

    auto dp = std::vector(n1 + 1, std::vector(n2 + 1, std::array<int, 2>()));
    dp[0][0][0] = dp[0][0][1] = 1;

    for (int i = 0; i <= n1; ++i)
    {
        for (int j = 0; j <= n2; ++j)
        {
            for (int k = 1; k <= std::min(i, k1); ++k)
            {
                dp[i][j][0] = (dp[i][j][0] + dp[i - k][j][1]) % mod;
            }

            for (int k = 1; k <= std::min(j, k2); ++k)
            {
                dp[i][j][1] = (dp[i][j][1] + dp[i][j - k][0]) % mod;
            }
        }
    }

    std::cout << (dp[n1][n2][0] + dp[n1][n2][1]) % mod << "\n";
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
