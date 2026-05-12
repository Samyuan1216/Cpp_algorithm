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
    i64 n, k;
    std::cin >> n >> k;

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    auto check = [&](i64 mid) -> bool
    {
        i64 cnt = 0;
        for (int i = 0; i < n; ++i)
        {
            if (arr[i] >= mid)
            {
                continue;
            }

            cnt += (mid - arr[i] + i) / (i + 1);
            if (cnt > k)
            {
                return false;
            }
        }

        return true;
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

    std::cout << *find(0ll, i64(2e18), false) << "\n";
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
