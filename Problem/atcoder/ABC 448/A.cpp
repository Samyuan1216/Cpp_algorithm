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
    int n, x;
    std::cin >> n >> x;

    for (int i = 0, num; i < n; ++i)
    {
        std::cin >> num;

        if (num < x)
        {
            x = num;
            std::cout << 1 << "\n";
        }
        else
        {
            std::cout << 0 << "\n";
        }
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
