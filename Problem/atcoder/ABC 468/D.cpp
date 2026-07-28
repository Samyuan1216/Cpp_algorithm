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
    std::string str;
    std::cin >> str;

    int n = std::ssize(str);
    auto status = std::vector(n, std::vector<int>(n, -1));

    for (int i = 0; i < n; ++i)
    {
        status[i][i] = 0;
    }

    for (int i = 0; i < n - 1; ++i)
    {
        status[i][i + 1] = (str[i] == str[i + 1]? 0: 1);
    }

    std::vector<int> dp(n, 2);
    for (int i = 2; i < n; ++i)
    {
        for (int j = 0; j < i - 1; ++j)
        {
            if (status[j + 1][i - 1] >= 0 && (str[i] != str[j]) + status[j + 1][i - 1] <= 1)
            {
                ++dp[i];
                status[j][i] = (str[i] != str[j]) + status[j + 1][i - 1];
            }
        }
    }

    i64 ans = 0;
    for (int i = 0; i < n; ++i)
    {
        ans += dp[i];
    }

    std::cout << ans - 1 << "\n";
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
