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
    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    std::vector<std::vector<int>> index(n + 1);
    for (int i = 0; i < n; ++i)
    {
        index[arr[i]].push_back(i);
    }

    std::vector<int> dp(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        dp[i] = dp[i - 1];

        int idx = std::distance(index[arr[i - 1]].begin(), ranges::lower_bound(index[arr[i - 1]], i - 1));
        if (idx + 1 >= arr[i - 1])
        {
            int j = index[arr[i - 1]][idx - arr[i - 1] + 1];
            dp[i] = std::max(dp[i], dp[j] + arr[i - 1]);
        }
    }

    std::cout << dp[n] << "\n";
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
