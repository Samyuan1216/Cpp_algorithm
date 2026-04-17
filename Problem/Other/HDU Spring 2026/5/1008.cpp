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
    int n, k;
    std::cin >> n >> k;

    std::vector<i64> arr(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];
    }

    std::vector<i64> sum(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        sum[i] = sum[i - 1] + arr[i];
    }

    std::vector<i64> dp(n + 2);
    std::deque<int> q;
    for (int i = n; i >= 1; --i)
    {
        while (!q.empty() && sum[i] / 2 + dp[i + 1] <= sum[q.back()] / 2 + dp[q.back() + 1])
        {
            q.pop_back();
        }

        while (!q.empty() && q.front() > i + k)
        {
            q.pop_front();
        }

        q.push_back(i);

        dp[i] = arr[i] - sum[i] / 2 + sum[q.front()] / 2 + dp[q.front() + 1];
    }

    std::cout << dp[1] << "\n";
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
