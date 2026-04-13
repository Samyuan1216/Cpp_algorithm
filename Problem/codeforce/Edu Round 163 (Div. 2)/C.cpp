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

    auto grid = std::vector(2, std::string());
    for (auto &str: grid)
    {
        std::cin >> str;
    }

    auto dp = std::vector(2, std::vector<bool>(n));
    dp[0][0] = 2;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            if (!dp[j][i])
            {
                continue;
            }

            if (i < n - 1)
            {
                if (grid[j][i + 1] == '>')
                {
                    dp[j][i + 2] = true;
                }
            }

            if (j == 0)
            {
                if (grid[j + 1][i] == '>')
                {
                    dp[j + 1][i + 1] = true;
                }
            }

            if (j == 1)
            {
                if (grid[j - 1][i] == '>')
                {
                    dp[j - 1][i + 1] = true;
                }
            }
        }
    }

    std::cout << (dp[1][n - 1]? "YES\n": "NO\n");
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
