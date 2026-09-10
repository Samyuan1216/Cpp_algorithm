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
    i64 x, y, k;
    std::cin >> x >> y >> k;

    while (x > 1)
    {
        i64 time = y - x % y;
        if (k < time)
        {
            std::cout << x + k << "\n";
            return;
        }

        x += time;
        k -= time;

        while (x % y == 0)
        {
            x /= y;
        }
    }

    i64 rem = k % (y - 1);
    std::cout << x + rem << "\n";
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
