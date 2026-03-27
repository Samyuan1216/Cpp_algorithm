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

    auto check = [&](int mid)
    {
        return i64(mid + 1) * (mid + 2 * n) >= 2 * k;
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
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
    
        return ans;
    };

    std::cout << *find(0, 100000000) << "\n";
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
