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

    constexpr int INF = 1e9;
    auto dp = std::vector(n, std::array<int, 3>{INF, INF, INF});
    dp[0][0] = 1;

    if (arr[0] >= 2)
    {
        dp[0][1] = 0;
    }
    
    if (arr[0] & 1)
    {
        dp[0][2] = 0;
    }

    for (int i = 1; i < n; ++i)
    {
        dp[i][0] = *ranges::min_element(dp[i - 1]) + 1;
        if (arr[i] >= 2)
        {
            dp[i][1] = std::min(dp[i - 1][0], dp[i - 1][2]);
        }

        if (arr[i] & 1)
        {
            dp[i][2] = std::min(dp[i - 1][0], dp[i - 1][1]);
        }
    }

    std::cout << *ranges::min_element(dp[n - 1]) << "\n";
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
