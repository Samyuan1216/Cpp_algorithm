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
    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    if (n == 1)
    {
        std::cout << arr[0] << "\n";
        return;
    }

    constexpr int INF = 1e9;
    auto dp = std::vector(n, std::array<int, 2>{INF, INF});
    dp[0][1] = arr[0], dp[1][0] = dp[0][1], dp[1][1] = dp[0][1] + arr[1];

    for (int i = 2; i < n; ++i)
    {
        dp[i][0] = std::min(dp[i - 1][1], dp[i - 2][1]);
        dp[i][1] = std::min(dp[i - 1][0] + arr[i], dp[i - 2][0] + arr[i] + arr[i - 1]);
    }

    std::cout << std::min(dp[n - 1][0], dp[n - 1][1]) << "\n";
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
