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
    int n = 10;

    auto flat_index = [](auto ...D)
    {
        return [=](auto ...i)
        {
            int idx = 0;
            ((idx = idx * D + i), ...);
    
            return idx;
        };
    };
    auto idx = flat_index(n, 2, 2, 2);

    std::string low, high;

    std::vector<int> dp(n * 2 * 2 * 2, -1);
    auto digit_dp = [&](this auto &&digit_dp, int i, bool limit_low, bool limit_high, bool is_num) -> int
    {
        if (i == n)
        {
            return (is_num? 1: 0);
        }
    
        if (dp[idx(i, limit_low, limit_high, is_num)] != -1)
        {
            return dp[idx(i, limit_low, limit_high, is_num)];
        }
    
        int ans = 0;
        if (!is_num && low[i] == '0')
        {
            ans += digit_dp(i + 1, true, false, false);
        }
    
        int lo = (limit_low? (low[i] - '0'): 0), hi = (limit_high? (high[i] - '0'): 0), d0 = (is_num? 0: 1);
        for (int d = std::min(lo, d0); d <= hi; ++d)
        {
            ans += digit_dp(i + 1, limit_low && d == lo, limit_high && d == hi, true);
        }
    
        dp[idx(i, limit_low, limit_high, is_num)] = ans;
        return ans;
    };
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
