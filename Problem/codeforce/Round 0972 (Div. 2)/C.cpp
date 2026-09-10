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

    std::vector<std::string> arr(n);
    for (auto &str: arr)
    {
        std::cin >> str;
    }

    std::map<char, int> dp;
    std::string aim = "narek";

    constexpr int INF = -1e9;
    for (auto &c: aim)
    {
        dp[c] = INF;
    }
    dp['n'] = 0;

    for (auto &str: arr)
    {
        auto old = dp;
        for (int i = 0; i < 5; ++i)
        {
            if (old[aim[i]] == INF)
            {
                continue;
            }

            int j = i, scoren = 0, scorec = 0;
            for (auto &c: str)
            {
                if (c == aim[j])
                {
                    j = (j + 1) % 5;
                    if (c == 'k')
                    {
                        scoren += 5;
                    }
                }
                else if (c == 'n' || c == 'a' || c == 'r' || c == 'e' || c == 'k')
                {
                    ++scorec;
                }
            }

            dp[aim[j]] = std::max(dp[aim[j]], old[aim[i]] + scoren - scorec);
        }
    }

    int ans = 0;
    for (int i = 0; i < 5; ++i)
    {
        ans = std::max(ans, dp[aim[i]] - i);
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
