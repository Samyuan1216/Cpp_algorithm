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

    std::vector<i64> a(n);
    for (auto &x: a)
    {
        std::cin >> x;
    }

    std::vector<i64> b(n);
    for (auto &x: b)
    {
        std::cin >> x;
    }

    std::vector<i64> pre(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        pre[i] = pre[i - 1] + a[i - 1] * b[i - 1];
    }

    std::vector<i64> suf(n + 2);
    for (int i = n; i >= 1; --i)
    {
        suf[i] = suf[i + 1] + a[i - 1] * b[i - 1];
    }

    auto dp = std::vector(n, std::vector<i64>(n + 1));
    i64 ans = 0;

    for (int i = 0; i < n; ++i)
    {
        dp[i][1] = a[i] * b[i];
        ans = std::max(ans, pre[i] + dp[i][1] + suf[i + 2]);

        for (int len = 2; len <= i + 1; ++len)
        {
            dp[i][len] = a[i] * b[i - len + 1] + a[i - len + 1] * b[i] + dp[i - 1][len - 2];
            ans = std::max(ans, pre[i - len + 1] + dp[i][len] + suf[i + 2]);
        }
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
