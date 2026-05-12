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

    std::vector<int> w(n);
    std::vector<i64> v(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> w[i] >> v[i];
    }

    std::vector<i64> dp(limit + 1);
    for (int i = 0; i < n; ++i)
    {
        for (int j = limit; j >= w[i]; --j)
        {
            dp[j] = std::max(dp[j], dp[j - w[i]] + v[i]);
        }
    }

    std::cout << dp[limit] << "\n";
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
