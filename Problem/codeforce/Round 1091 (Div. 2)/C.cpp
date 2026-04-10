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
    int n, m, a, b;
    std::cin >> n >> m >> a >> b;

    if (std::gcd(n, a) >= 2 || std::gcd(m, b) >= 2 || std::gcd(n, m) > 2)
    {
        std::cout << "NO\n";
    }
    else
    {
        std::cout << "YES\n";
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
