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
    auto s = std::string(), t = std::string();
    std::cin >> s >> t;

    int n = std::ssize(s), m = std::ssize(t);
    auto idx = std::vector(26, std::vector<int>());
    for (int i = m; i >= 1; --i)
    {
        idx[t[i - 1] - 'a'].push_back(i);
    }

    auto dp = std::vector<int>(m + 1);
    i64 ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (auto &j: idx[s[i - 1] - 'a'])
        {
            if (j == 1)
            {
                dp[1] = i;
            }
            else
            {
                dp[j] = dp[j - 1];
            }
        }

        ans += (i - dp[m]);
    }

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
