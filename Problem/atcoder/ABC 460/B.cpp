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
    i64 x1, y1, r1, x2, y2, r2;
    std::cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

    i64 tmp1 = std::pow(x1 - x2, 2), tmp2 = std::pow(y1 - y2, 2);
    i64 r3 = std::pow(r1 + r2, 2), r4 = std::pow(r1 - r2, 2);
    std::cout << (tmp1 + tmp2 <= r3 && tmp1 + tmp2 >= r4? "Yes\n": "No\n");
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
