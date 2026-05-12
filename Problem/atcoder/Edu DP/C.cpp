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

    std::vector<std::array<int, 3>> active(n);
    for (auto &[a, b, c]: active)
    {
        std::cin >> a >> b >> c;
    }

    std::vector<std::array<int, 3>> dp(n);
    dp[0] = active[0];

    for (int i = 1; i < n; ++i)
    {
        dp[i][0] = active[i][0] + std::max(dp[i - 1][1], dp[i - 1][2]);
        dp[i][1] = active[i][1] + std::max(dp[i - 1][0], dp[i - 1][2]);
        dp[i][2] = active[i][2] + std::max(dp[i - 1][0], dp[i - 1][1]);
    }

    std::cout << *ranges::max_element(dp[n - 1]) << "\n";
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
