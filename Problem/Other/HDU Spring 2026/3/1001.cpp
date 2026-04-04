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
    int n, m;
    std::cin >> n >> m;

    auto a = std::vector<i64>(n);
    for (auto &x: a)
    {
        std::cin >> x;
    }

    auto b = std::vector<i64>(n + 1);
    for (auto &x: b)
    {
        std::cin >> x;
    }

    ranges::sort(a, std::greater<>());
    ranges::sort(b, std::greater<>());

    using i128 = __int128_t;
    auto pre = std::vector<i128>(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        pre[i] = pre[i - 1] + i128(a[i - 1]) * b[i - 1];
    }

    auto suf = std::vector<i128>(n + 2);
    for (int i = n; i >= 1; --i)
    {
        suf[i] = suf[i + 1] + i128(a[i - 1]) * b[i];
    }

    auto check = [&](i128 mid)
    {
        int k = std::distance(a.begin(), ranges::lower_bound(a, mid, std::greater<>()));
        return pre[k] + mid * b[k] + suf[k + 1] >= m;
    };

    auto find = [&](auto l, auto r, bool find_first = true)
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

    std::cout << *find(0, 1000000000) << "\n";
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
