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
    int n, m;
    std::cin >> n >> m;

    std::vector grid(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            std::cin >> grid[i][j];
        }
    }

    if ((n + m) % 2 == 0)
    {
        std::cout << "NO\n";
        return;
    }

    std::vector dp(n, std::vector<std::bitset<2010>>(m));
    if (grid[0][0] == 1)
    {
        dp[0][0][1] = 1;
    }
    else
    {
        dp[0][0][0] = 1;
    }

    for (int i = 1; i < n; ++i)
    {
        if (grid[i][0] == 1)
        {
            dp[i][0] = dp[i - 1][0] << 1;
        }
        else
        {
            dp[i][0] = dp[i - 1][0];
        }
    }

    for (int j = 1; j < m; ++j)
    {
        if (grid[0][j] == 1)
        {
            dp[0][j] = dp[0][j - 1] << 1;
        }
        else
        {
            dp[0][j] = dp[0][j - 1];
        }
    }

    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j < m; ++j)
        {
            if (grid[i][j] == 1)
            {
                dp[i][j] = (dp[i - 1][j] << 1) | (dp[i][j - 1] << 1);
            }
            else
            {
                dp[i][j] = dp[i - 1][j] | dp[i][j - 1];
            }
        }
    }

    std::cout << (dp[n - 1][m - 1][(n + m) / 2]? "YES\n": "NO\n");
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
