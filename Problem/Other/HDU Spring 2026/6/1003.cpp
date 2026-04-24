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
    int s1, s2;
    std::cin >> s1 >> s2;

    if (s2 < 45)
    {
        std::cout << "0.0" << "\n";
        return;
    }

    int s = (s1 * 6 + s2 * 4 + 9) / 10;
    if (s >= 95)
    {
        std::cout << std::format("{:.1f}\n", 5.0);
    }
    else if (s < 60)
    {
        std::cout << std::format("0.0\n");
    }
    else
    {
        std::cout << std::format("{:.1f}\n", 5.0 - 0.1 * (95 - s));
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
