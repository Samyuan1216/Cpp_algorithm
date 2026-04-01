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

    auto cnt = [](int num) -> int
    {
        int ans = 0;
        for (int i = 1; i <= num; ++i)
        {
            if (num % i == 0)
            {
                ++ans;
            }
        }

        return ans;
    };

    if (x == y)
    {
        std::cout << 1 << "\n";
    }
    else
    {
        std::cout << cnt(std::abs(x - y)) << "\n";
    }

    for (int i = 0; i < x; ++i)
    {
        std::cout << "1 ";
    }

    for (int i = 0; i < y; ++i)
    {
        std::cout << "-1 ";
    }
    std::cout << "\n";
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
