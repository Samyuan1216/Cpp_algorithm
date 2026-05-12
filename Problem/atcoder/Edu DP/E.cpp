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
    int n, limit;
    std::cin >> n >> limit;

    std::vector<i64> w(n);
    std::vector<int> v(n);

    int sum = 0;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> w[i] >> v[i];

        sum += v[i];
    }

    std::vector<i64> dp(sum + 1, 1e18);
    dp[0] = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = sum; j >= v[i]; --j)
        {
            dp[j] = std::min(dp[j], dp[j - v[i]] + w[i]);
        }
    }

    for (int i = sum; i >= 0; --i)
    {
        if (dp[i] <= limit)
        {
            std::cout << i << "\n";
            break;
        }
    }
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
