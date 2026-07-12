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
    int n, k;
    std::cin >> n >> k;

    std::vector<i64> arr(n);
    i64 sum = 0;

    for (int a, b; auto &x: arr)
    {
        std::cin >> a >> b;

        x = b - a;
        sum += a;
    }

    auto flat_index = [](auto ...D)
    {
        return [=](auto ...i)
        {
            int idx = 0;
            ((idx = idx * D + i), ...);
    
            return idx;
        };
    };
    auto idx = flat_index(k + 1, n + 1);

    constexpr i64 INF = -1e9;
    std::vector<i64> f((k + 1) * (n + 1), INF), dp((k + 1) * (n + 1), INF);
    ranges::fill(dp.begin(), dp.begin() + n + 1, 0);

    for (int i = 1; i <= k; ++i)
    {
        for (int j = i; j <= n; ++j)
        {
            f[idx(i, j)] = std::max(f[idx(i, j - 1)], dp[idx(i - 1, j - 1)]) + arr[j - 1];
            dp[idx(i, j)] = std::max(dp[idx(i, j - 1)], f[idx(i, j)]);
        }
    }

    i64 ans = sum;
    for (int i = 1; i <= k; ++i)
    {
        ans = std::max(ans, sum + dp[idx(i, n)]);
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
