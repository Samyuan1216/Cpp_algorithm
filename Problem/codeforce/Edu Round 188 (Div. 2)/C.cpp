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
    i64 a, b, c, m;
    std::cin >> a >> b >> c >> m;

    i64 ab = std::lcm(a, b), ac = std::lcm(a, c), bc = std::lcm(b, c), abc = std::lcm(std::lcm(a, b), c);
    i64 ans_a = (m / a) * 6 - (m / ab + m / ac) * 3 + (m / abc) * 2;
    i64 ans_b = (m / b) * 6 - (m / ab + m / bc) * 3 + (m / abc) * 2;
    i64 ans_c = (m / c) * 6 - (m / ac + m / bc) * 3 + (m / abc) * 2;

    std::cout << ans_a << " " << ans_b << " " << ans_c << "\n";
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
