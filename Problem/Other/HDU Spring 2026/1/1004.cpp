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
    i64 n, k;
    std::cin >> n >> k;

    auto check = [&](i64 mid) -> bool
    {
        if (mid == 0 || mid == 1)
        {
            return true;
        }

        i64 cur = 1;
        for (int i = 0; i < k; ++i)
        {
            if (cur > n / mid) 
            {
                return false;
            }
            cur *= mid;
        }

        return true;
    };

    auto find = [&](auto l, auto r)
    {
        std::optional<decltype(l)> ans;
        while (l <= r)
        {
            auto mid = std::midpoint(l, r);
            if (check(mid))
            {
                ans = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
    
        return ans;
    };

    i64 ans = *find(0ll, n); 
    std::cout << ans << "\n";
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
