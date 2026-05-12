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
    int n, k;
    std::cin >> n >> k;

    std::vector<int> h(n);
    for (auto &x: h)
    {
        std::cin >> x;
    }

    if (n == 1)
    {
        std::cout << 0 << "\n";
        return;
    }

    std::vector<int> dp(n, 2e9);
    dp[0] = 0, dp[1] = std::abs(h[0] - h[1]);

    for (int i = 2; i < n; ++i)
    {
        for (int j = 1; j <= k && i - j >= 0; ++j)
        {
            dp[i] = std::min(dp[i], dp[i - j] + std::abs(h[i] - h[i - j]));
        }
    }

    std::cout << dp[n - 1] << "\n";
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
