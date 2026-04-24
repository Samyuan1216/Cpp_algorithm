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

    std::vector<std::string> g(2);
    for (auto &str: g)
    {
        std::cin >> str;
    }

    std::vector<int> dp(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        dp[i] = dp[i - 1] + (g[0][i - 1] == g[1][i - 1]? 0: 1);
        if (i > 1)
        {
            dp[i] = std::min(dp[i], dp[i - 2] + (g[0][i - 1] == g[0][i - 2]? 0: 1) + (g[1][i - 1] == g[1][i - 2]? 0: 1));
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
