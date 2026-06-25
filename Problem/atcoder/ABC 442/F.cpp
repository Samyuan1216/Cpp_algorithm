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
    int n;
    std::cin >> n;

    std::vector<std::string> grid(n);
    for (auto &str: grid)
    {
        std::cin >> str;
    }

    auto d = std::vector(n, std::vector<int>(n + 1));
    {
        auto pre = std::vector(n, std::vector<int>(n + 1));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                pre[i][j] = pre[i][j - 1] + (grid[i][j - 1] == '#'? 1: 0);
            }
        }

        auto suf = std::vector(n, std::vector<int>(n + 1));
        for (int i = 0; i < n; ++i)
        {
            for (int j = n - 1; j >= 0; --j)
            {
                suf[i][j] = suf[i][j + 1] + (grid[i][j] == '.'? 1: 0);
            }
        }

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j <= n; ++j)
            {
                d[i][j] = pre[i][j] + suf[i][j];
            }
        }
    }

    auto dp = std::vector(n, std::vector<int>(n + 1));
    for (int i = 0; i < n; ++i)
    {
        std::vector<int> sufmin(n + 1);
        if (i > 0)
        {
            sufmin[n] = dp[i - 1][n];
            for (int j = n - 1; j >= 0; --j)
            {
                sufmin[j] = std::min(sufmin[j + 1], dp[i - 1][j]);
            }
        }

        for (int j = 0; j <= n; ++j)
        {
            dp[i][j] = d[i][j] + sufmin[j];
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
