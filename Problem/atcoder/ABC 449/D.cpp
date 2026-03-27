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
    int l, r, d, u;
    std::cin >> l >> r >> d >> u;

    i64 ans = 0;
    for (int x = (l & 1? l + 1: l); x <= r; x += 2)
    {
        ans += std::max(0, std::min(std::abs(x) - 1, u) - std::max(-std::abs(x) + 1, d) + 1);
    }

    for (int y = (d & 1? d + 1: d); y <= u; y += 2)
    {
        ans += std::max(0, std::min(std::abs(y), r) - std::max(-std::abs(y), l) + 1);
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
