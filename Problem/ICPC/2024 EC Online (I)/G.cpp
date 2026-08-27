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
    i64 n;
    std::cin >> n;

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    auto check = [&](i64 mid) -> bool
    {
        std::vector<i64> pre(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            pre[i] = pre[i - 1] + (arr[i - 1] >= mid? 1: -1);
        }

        std::vector<i64> dp(n + 1);
        i64 good = 0;

        for (int l = n; l >= 1; --l)
        {
            i64 sum = 0;
            for (int r = l; r <= n; ++r)
            {
                sum += (pre[r] - pre[l - 1] > 0? 1: -1);
                dp[r] += sum;

                if (dp[r] > 0)
                {
                    ++good;
                }
            }
        }

        return 2ll * good > n * (n + 1) / 2ll;
    };

    auto find = [&](auto l, auto r, bool find_first = true) -> std::optional<decltype(l)>
    {
        std::optional<decltype(l)> ans;
        while (l <= r)
        {
            auto mid = std::midpoint(l, r);
            if (check(mid))
            {
                ans = mid;
                find_first? (r = mid - 1): (l = mid + 1);
            }
            else
            {
                find_first? (l = mid + 1): (r = mid - 1);
            }
        }
    
        return ans;
    };

    std::cout << *find(1ll, i64(1e9 + 10), false) << "\n";
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
