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
    std::string str;
    std::cin >> n >> str;

    std::vector<int> x(n);
    for (auto &num: x)
    {
        std::cin >> num;
    }

    std::vector<int> y(n - 1);
    for (auto &num: y)
    {
        std::cin >> num;
    }

    std::vector<std::array<i64, 2>> dp(n);
    if (str[0] == 'S')
    {
        dp[0][1] = -x[0];
    }
    else
    {
        dp[0][0] = -x[0];
    }

    for (int i = 1; i < n; ++i)
    {
        dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + y[i - 1]) + (str[i] == 'S'? 0: -x[i]);
        dp[i][1] = std::max(dp[i - 1][0], dp[i - 1][1]) + (str[i] == 'R'? 0: -x[i]);
    }

    std::cout << std::max(dp[n - 1][0], dp[n - 1][1]) << "\n";
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
