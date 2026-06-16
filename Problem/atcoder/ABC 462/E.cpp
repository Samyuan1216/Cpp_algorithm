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
    i64 a, b, x, y;
    std::cin >> a >> b >> x >> y;

    x = std::abs(x), y = std::abs(y);
    i64 cost = std::min(3 * std::min(a, b), std::max(a, b));
    i64 ans = 2 * std::min(a, b) * std::min(x, y) + std::abs(x - y) / 2 * (cost + std::min(a, b));

    if (std::abs(x - y) & 1)
    {
        if ((x > y) == (a > b))
        {
            ans += cost;
        }
        else
        {
            ans += std::min(a, b);
        }
    }

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
