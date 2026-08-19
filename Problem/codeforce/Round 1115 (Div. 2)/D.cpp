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
    int n;
    std::cin >> n;

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    std::vector<i64> d(n);
    d[0] = arr[0];

    for (int i = 1; i < n; ++i)
    {
        d[i] = arr[i] - arr[i - 1];
    }

    auto is_odd = [&](i64 x) -> bool
    {
        return x % 2 != 0;
    };

    for (int l = 1, r = 1; r < n;)
    {
        while (r < n && is_odd(d[l]) == is_odd(d[r]))
        {
            ++r;
        }

        ranges::sort(d.begin() + l, d.begin() + r);

        l = r;
    }

    for (int i = 0; i < n; ++i)
    {
        d[i] += (i > 0? d[i - 1]: 0);
        std::cout << d[i] << " \n"[i == n - 1];
    }
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
