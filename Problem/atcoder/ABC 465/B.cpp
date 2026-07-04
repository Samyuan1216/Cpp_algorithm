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
    int x, y, l, r, a, b;
    std::cin >> x >> y >> l >> r >> a >> b;

    if (a < l && b > r)
    {
        std::cout << (l - a + b - r) * y + (r - l) * x << "\n";
        return;
    }

    if (b < l)
    {
        std::cout << (b - a) * y << "\n";
    }
    else if (a < l)
    {
        std::cout << (l - a) * y + (b - l) * x << "\n";
    }
    else if (b <= r)
    {
        std::cout << (b - a) * x << "\n";
    }
    else if (a <= r)
    {
        std::cout << (r - a) * x + (b - r) * y << "\n";
    }
    else
    {
        std::cout << (b - a) * y << "\n";
    }
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
