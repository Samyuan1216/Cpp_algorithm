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
    int n;
    std::cin >> n;

    int ans = 0, status;
    for (int i = 1; i < 2 * n - 1; i += 2)
    {
        std::cout << std::format("? {} {}",i, i + 1) << std::endl;
        std::cin >> status;

        if (status == 1)
        {
            ans = i;
            break;
        }
    }

    if (status == 1)
    {
        std::cout << std::format("! {}", ans) << std::endl;
        return;
    }

    std::cout << std::format("? 1 {}", 2 * n - 1) << std::endl;
    std::cin >> status;

    if (status == 1)
    {
        std::cout << std::format("! {}", 2 * n - 1) << std::endl;
        return;
    }

    std::cout << std::format("? 2 {}", 2 * n - 1) << std::endl;
    std::cin >> status;

    if (status == 1)
    {
        std::cout << std::format("! {}", 2 * n - 1) << std::endl;
        return;
    }

    std::cout << std::format("! {}", 2 * n) << std::endl;
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
