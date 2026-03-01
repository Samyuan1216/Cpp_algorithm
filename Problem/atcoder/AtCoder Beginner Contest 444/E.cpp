#include <bits/stdc++.h>
#include <bits/extc++.h>
namespace ranges = std::ranges;
namespace views = std::views;

using i64 = int64_t;
using i128 = __int128;
using u64 = uint64_t;
using u128 = unsigned __int128;
using f64 = double;
using f128 = long double;

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
    int n, d;
    std::cin >> n >> d;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    std::map<i64, int> mp;
    mp.emplace(lim<int>::max(), -1);
    mp.emplace(lim<int>::min(), -1);

    i64 ans = 0;
    for (int l = 0, r = 0; r < n; ++r)
    {
        auto iter = mp.lower_bound(arr[r]);
        auto next = iter, prev = std::prev(iter);

        int index = -1;
        if (std::abs(next->first - arr[r]) < d)
        {
            index = next->second;
        }

        if (std::abs(prev->first - arr[r]) < d)
        {
            index = std::max(index, prev->second);
        }

        while (l <= index)
        {
            mp.erase(arr[l]);
            l++;
        }

        mp.emplace(arr[r], r);
        ans += r - l + 1;
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
