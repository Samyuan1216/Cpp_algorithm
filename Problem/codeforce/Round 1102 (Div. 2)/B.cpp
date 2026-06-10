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
    i64 n;
    std::cin >> n;

    if (n == 10)
    {
        std::cout << -1 << "\n";
        return;
    }

    i64 a = n % 12, b = n - a;
    if (a == 10)
    {
        a += 12;
        b -= 12;
    }

    std::cout << a << " " << b << "\n";
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
