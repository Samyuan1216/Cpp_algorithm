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

    auto arr = std::vector<i64>(100010);
    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;

        ++arr[x];
    }

    for (int i = 0; i <= 100000; ++i)
    {
        arr[i] *= i;
    }

    auto dp = std::vector<i64>(100010);
    dp[1] = arr[1];

    for (int i = 2; i <= 100000; ++i)
    {
        dp[i] = std::max(dp[i - 1], dp[i - 2] + arr[i]);
    }

    std::cout << dp[100000] << "\n";
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
