#include <bits/extc++.h>
namespace ranges = std::ranges;
namespace pbds = __gnu_pbds;

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

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    auto check = [&](int mid) -> bool
    {
        std::multiset<int> s;
        for (auto &x: arr)
        {
            s.insert(x);
        }

        for (int i = mid - 1; i >= 0; --i)
        {
            if (auto iter = s.find(i); iter != s.end())
            {
                s.erase(iter);
            }
            else
            {
                if (auto iter = s.upper_bound(2 * i); iter != s.end())
                {
                    s.erase(iter);
                }
                else
                {
                    return false;
                }
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

    std::cout << *find(0, n, false) << "\n";
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
