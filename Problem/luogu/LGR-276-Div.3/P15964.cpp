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
    auto a = std::vector<i64>(901234);
    a[0] = 789456;
    for (int i = 1; i < 901234; ++i)
    {
        a[i] = a[i - 1] + 567890;
    }

    auto b = std::vector<i64>(500001);
    b[0] = 654321;
    for (int i = 1; i < 500001; ++i)
    {
        b[i] = b[i - 1] + 876543;
    }

    i64 ans = 0;
    for (int i = 0; i < 901234; ++i)
    {
        ans += std::distance(ranges::upper_bound(b, a[i]), b.end());
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
