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
    int n, a, b;
    std::cin >> n >> a >> b;

    if ((n & 1) || (a + b) % 2 == 0)
    {
        std::cout << "No\n";
        return;
    }

    std::cout << "Yes\n";

    for (int i = 0; i < (a - 1) / 2; ++i)
    {
        std::cout << std::string(n - 1, 'R');
        std::cout << "D";
        std::cout << std::string(n - 1, 'L');
        std::cout << "D";
    }

    if (a & 1)
    {
        std::cout << "DR";
        for (int i = 0; i < (b - 1) / 2; ++i)
        {
            std::cout << "URDR";
        }

        for (int i = 0; i < (n - b) / 2; ++i)
        {
            std::cout << "RURD";
        }
    }
    else
    {
        for (int i = 0; i < b / 2; ++i)
        {
            std::cout << "DRUR";
        }

        for (int i = 0; i < (n - b) / 2; ++i)
        {
            std::cout << "RDRU";
        }

        std::cout << "RD";
    }

    for (int i = 0; i < (n - a) / 2; ++i)
    {
        std::cout << "D";
        std::cout << std::string(n - 1, 'L');
        std::cout << "D";
        std::cout << std::string(n - 1, 'R');
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
