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

    i64 sum = 0;
    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;

        sum += x;
    }

    std::vector<i64> dp1(n);
    dp1[0] = arr[0];

    for (int i = 1; i < n - 1; ++i)
    {
        dp1[i] = std::max(dp1[i - 1] + arr[i], arr[i]);
    }

    std::vector<i64> dp2(n);
    dp2[1] = arr[1];

    for (int i = 2; i < n; ++i)
    {
        dp2[i] = std::max(dp2[i - 1] + arr[i], arr[i]);
    }

    std::cout << (sum > std::max(*ranges::max_element(dp1), *ranges::max_element(dp2))? "YES\n": "NO\n");
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
