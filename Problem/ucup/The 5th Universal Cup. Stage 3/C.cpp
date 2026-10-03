#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

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
    int r;
    std::cin >> r;

    std::cout << std::format("{} {}\n", 0, r);
    std::cout << std::format("{} {}\n", -r, 0);
    std::cout << std::format("{} {}\n", 0, -r);
    std::cout << std::format("{} {}\n", r, 0);
    std::cout << std::format("{} {}\n", r, r);
    std::cout << std::format("{} {}\n", -r, -r);
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
