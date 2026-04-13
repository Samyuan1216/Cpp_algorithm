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

    auto w = std::vector<int>(1000010);
    for (int i = 0, a, b; i < n; ++i)
    {
        std::cin >> a >> b;

        w[a] = b;
    }

    auto dp = std::vector<int>(1000010);
    dp[0] = (w[0] > 0? 1: 0);

    for (int i = 1; i <= 1000000; ++i)
    {
        if (w[i] == 0)
        {
            dp[i] = dp[i - 1];
            continue;
        }

        dp[i] = (i - w[i] - 1 < 0? 1: dp[i - w[i] - 1] + 1);
    }

    std::cout << n - *ranges::max_element(dp) << "\n";
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
