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
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;

    c = c - a, d = d - b;
    if (a > b)
    {
        std::swap(a, b);
    }

    if (c > d)
    {
        std::swap(c, d);
    }

    std::cout << ((b + a) / (a + 1) < 3 && (d + c) / (c + 1) < 3? "YES\n": "NO\n");
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
