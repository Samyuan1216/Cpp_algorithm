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
    int n;
    std::cin >> n;

    std::cout << std::format("? {} {}", 1, n) << std::endl;

    int cnt1;
    std::cin >> cnt1;

    if (cnt1 == 0)
    {
        std::cout << "! NO" << std::endl;
        return;
    }

    std::cout << std::format("? {} {}", 1, cnt1) << std::endl;

    int cnt2;
    std::cin >> cnt2;

    std::cout << "! " << (cnt1 != cnt2? "YES": "NO") << std::endl;
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