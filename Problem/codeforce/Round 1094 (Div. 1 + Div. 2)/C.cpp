#include <bits/extc++.h>
namespace ranges = std::ranges;
namespace pbds = __gnu_pbds;

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

    std::vector<int> arr(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];
    }

    std::vector<int> sorted = arr;
    ranges::sort(sorted.begin() + 1, sorted.end());

    int x = sorted[(n + 1) / 2];
    std::vector<int> low(n + 1), high(n + 1), equel(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        low[i] = low[i - 1] + (arr[i] < x? 1: 0);
        high[i] = high[i - 1] + (arr[i] > x? 1: 0);
        equel[i] = equel[i - 1] + (arr[i] == x? 1: 0);
    }

    std::vector<int> dp(n + 1, -1);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i)
    {
        for (int k = 0; k < i; ++k)
        {
            if (dp[k] < 0 || (i - k) % 2 == 0)
            {
                continue;
            }

            if (std::abs((low[i] - low[k]) - (high[i] - high[k])) <= equel[i] - equel[k])
            {
                dp[i] = std::max(dp[i], dp[k] + 1);
            }
        }
    }

    std::cout << dp[n] << "\n";
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
