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

    std::vector<int> dp(n);
    dp[1] = std::abs(h[0] - h[1]);

    for (int i = 2; i < n; ++i)
    {
        dp[i] = std::min(dp[i - 1] + std::abs(h[i] - h[i - 1]), dp[i - 2] + std::abs(h[i] - h[i - 2]));
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
