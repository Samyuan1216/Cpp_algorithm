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
    int n, len;
    std::cin >> n;
    len = n * 2;

    std::vector<int> arr(len), l(n + 1, -1), r(n + 1, -1);
    for (int i = 0; i < len; ++i)
    {
        std::cin >> arr[i];

        if (l[arr[i]] == -1)
        {
            l[arr[i]] = i;
        }
        else
        {
            r[arr[i]] = i;
        }
    }

    std::vector<int> ord(len, -1);
    for (int x = 1; x <= n; ++x)
    {
        ord[r[x]] = x;
    }

    std::vector<i64> dp(len);
    for (int i = 0; i < len; ++i)
    {
        dp[i] = (i > 0? dp[i - 1]: 0);
        if (ord[i] != -1)
        {
            i64 w = std::pow(r[ord[i]] - l[ord[i]] + 1, 2) - (r[ord[i]] - l[ord[i]] + 1);
            dp[i] = std::max(dp[i], (l[ord[i]] > 0? dp[l[ord[i]] - 1]: 0) + w);
        }
    }

    std::cout << len + dp[len - 1] << "\n";
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
