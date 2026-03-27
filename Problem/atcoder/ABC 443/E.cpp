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
    int n, c;
    std::cin >> n >> c;

    auto g = std::vector<std::string>(n);
    for (auto &str: g)
    {
        std::cin >> str;
    }

    auto dp = std::vector<bool>(n);
    dp[c - 1] = true;

    auto clear = std::vector<bool>(n, true);
    for (int i = 0; i < n; ++i)
    {
        if (g[n - 1][i] == '#')
        {
            clear[i] = clear[i] && dp[i];
        }
    }

    for (int i = n - 2; i >= 0; --i)
    {
        auto tmp = std::vector<bool>(n);
        for (int j = 0; j < n; ++j)
        {
            bool status = false;
            if ((j > 0 && dp[j - 1]) || dp[j] || (j < n - 1 && dp[j + 1]))
            {
                status = true;
            }

            if (status)
            {
                if (g[i][j] == '.')
                {
                    tmp[j] = true;
                }
                else
                {
                    if (clear[j])
                    {
                        tmp[j] = true;
                    }
                }
            }
        }

        for (int j = 0; j < n; ++j)
        {
            if (g[i][j] == '#')
            {
                clear[j] = clear[j] && tmp[j];
            }
        }

        dp = tmp;
    }

    auto ans = std::string();
    for (int i = 0; i < n; ++i)
    {
        ans += (dp[i]? '1': '0');
    }

    std::cout << ans << "\n";
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
