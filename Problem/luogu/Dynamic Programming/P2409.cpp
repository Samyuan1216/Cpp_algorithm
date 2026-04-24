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
    int n, k;
    std::cin >> n >> k;

    std::vector<std::vector<int>> arr(n + 1);
    int sum = 0;

    for (int i = 1, m; i <= n; ++i)
    {
        std::cin >> m;

        arr[i].resize(m + 1);
        for (int j = 1; j <= m; ++j)
        {
            std::cin >> arr[i][j];
        }

        sum += *ranges::max_element(arr[i]);
    }

    auto dp = std::vector(n + 1, std::vector<int>(sum + 1));
    dp[0][0] = 1;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j < std::ssize(arr[i]); ++j)
        {
            for (int w = arr[i][j]; w <= sum; ++w)
            {
                dp[i][w] = std::min(k, dp[i][w] + dp[i - 1][w - arr[i][j]]);
            }
        }
    }

    for (int i = 0, cnt = 0; i <= sum; ++i)
    {
        for (int j = 1; j <= dp[n][i]; ++j)
        {
            std::cout << i << " ";

            if (++cnt == k)
            {
                std::cout << "\n";
                return;
            }
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
