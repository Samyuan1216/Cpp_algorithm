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
    int n, a, b, c;
    std::cin >> n >> a >> b >> c;

    auto dp = std::vector(n + 1, -1);
    dp[0] = 0;

    for (int i = a; i <= n; ++i)
    {
        if (dp[i - a] == -1)
        {
            continue;
        }

        dp[i] = std::max(dp[i], dp[i - a] + 1);
    }

    for (int i = b; i <= n; ++i)
    {
        if (dp[i - b] == -1)
        {
            continue;
        }

        dp[i] = std::max(dp[i], dp[i - b] + 1);
    }

    for (int i = c; i <= n; ++i)
    {
        if (dp[i - c] == -1)
        {
            continue;
        }

        dp[i] = std::max(dp[i], dp[i - c] + 1);
    }

    std::cout << dp[n] << "\n";
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
