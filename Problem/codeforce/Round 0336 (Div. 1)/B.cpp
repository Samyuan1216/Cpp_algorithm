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

    auto dp = std::vector(n, std::vector<int>(n, 1e9));
    for (int i = 0; i < n; ++i)
    {
        dp[i][i] = 1;
        if (i < n - 1)
        {
            dp[i][i + 1] = (arr[i] == arr[i + 1]? 1: 2);
        }
    }

    for (int len = 3; len <= n; ++len)
    {
        for (int l = 0, r = l + len - 1; r < n; ++l, ++r)
        {
            if (arr[l] == arr[r])
            {
                dp[l][r] = dp[l + 1][r - 1];
            }

            for (int k = l; k < r; ++k)
            {
                dp[l][r] = std::min(dp[l][r], dp[l][k] + dp[k + 1][r]);
            }
        }
    }

    std::cout << dp[0][n - 1] << "\n";
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
