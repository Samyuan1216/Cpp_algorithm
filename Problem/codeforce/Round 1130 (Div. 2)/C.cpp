#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

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
    i64 n, x;
    std::cin >> n >> x;

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    auto check = [&](i64 mid) -> bool
    {
        std::vector<i64> single;
        for (int i = 0; i < n; ++i)
        {
            if (!((i > 0 && arr[i] - arr[i - 1] <= mid) || (i + 1 < n && arr[i + 1] - arr[i] <= mid)))
            {
                single.push_back(arr[i]);
            }
        }

        int need = 0;
        for (int i = 0; i < std::ssize(single);)
        {
            ++need;
            if (i + 1 < std::ssize(single) && single[i + 1] - single[i] <= 2 * mid)
            {
                i += 2;
            }
            else
            {
                ++i;
            }
        }

        return need <= x;
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

    std::cout << *find(1, int(1e9)) << "\n";
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