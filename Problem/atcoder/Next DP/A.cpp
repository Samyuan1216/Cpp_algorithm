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

    if (n == 1)
    {
        std::cout << 1 << "\n";
        return;
    }

    std::vector<i64> dp(n + 1);
    dp[0] = dp[1] = 1;

    for (int i = 2; i <= n; ++i)
    {
        dp[i] += dp[i - 1] + dp[i - 2];
        for (int j = 0; j <= i - 3; ++j)
        {
            dp[i] += dp[j] * 2;
        }
    }

    std::cout << dp[n] << "\n";
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
