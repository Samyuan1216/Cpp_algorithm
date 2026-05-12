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
    std::string s1, s2;
    std::cin >> s1 >> s2;

    int n = std::ssize(s1), m = std::ssize(s2);
    auto dp = std::vector(n + 1, std::vector<int>(m + 1));
    auto path = std::vector(n + 1, std::vector<int>(m + 1));

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                path[i][j] = 0;
            }
            else if (dp[i - 1][j] >= dp[i][j - 1])
            {
                dp[i][j] = dp[i - 1][j];
                path[i][j] = 1;
            }
            else
            {
                dp[i][j] = dp[i][j - 1];
                path[i][j] = 2;
            }
        }
    }

    std::string ans;
    for (int i = n, j = m; i > 0 && j > 0;)
    {
        if (path[i][j] == 0)
        {
            ans += s1[i - 1];
            --i, --j;
        }
        else if (path[i][j] == 1)
        {
            --i;
        }
        else
        {
            --j;
        }
    }

    ranges::reverse(ans);
    std::cout << ans << "\n";
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
