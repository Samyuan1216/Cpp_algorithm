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
    int a, b;
    std::cin >> a >> b;

    if (a + b == 9 || a - b == 9 || a * b == 9 || (a % b == 0 && a / b == 9))
    {
        std::cout << "Nine\n";
    }
    else
    {
        std::cout << "Nein\n";
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
