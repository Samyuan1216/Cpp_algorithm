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
    int x, y;
    std::cin >> x >> y;

    if (x > y || (x == 0 && (x + y) % 2 == 0))
    {
        std::cout << "NO\n";
        return;
    }

    std::cout << "YES\n";

    int n = 2 * x + ((x + y) & 1? 1: 0), m = x + y - n, idx = 2;
    for (int i = 1; i < n; ++i, ++idx)
    {
        std::cout << idx - 1 << " " << idx << "\n";
    }

    for (int i = 1; i <= m; ++i, ++idx)
    {
        std::cout << 1 << " " << idx << "\n";
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
