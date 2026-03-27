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
    int r, g, b;
    std::cin >> r >> g >> b;

    int rg = 0, rb = 0, gb = 0;
    while ((r > 0 && g > 0) || (r > 0 && b > 0) || (g > 0 && b > 0))
    {
        if (r == std::min({r, g, b}))
        {
            --g, --b;
            ++gb;
        }
        else if (g == std::min({r, g, b}))
        {
            --r, --b;
            ++rb;
        }
        else
        {
            --r, --g;
            ++rg;
        }
    }

    if (r > 0)
    {
        std::cout << 'R';
        while (rg--)
        {
            std::cout << "GR";
        }

        bool status = (rb > 0? true: false);
        while (rb--)
        {
            std::cout << "BR";
        }

        while (gb--)
        {
            std::cout << (status? "BG": "GB");
        }
    }
    else if (g > 0)
    {
        std::cout << 'G';
        while (rg--)
        {
            std::cout << "RG";
        }

        bool status = (gb > 0? true: false);
        while (gb--)
        {
            std::cout << "BG";
        }

        while (rb--)
        {
            std::cout << (status? "BR": "RB");
        }
    }
    else
    {
        if (b > 0)
        {
            std::cout << 'B';
        }

        while (rb--)
        {
            std::cout << "RB";
        }

        bool status = (gb > 0? true: false);
        while (gb--)
        {
            std::cout << "GB";
        }

        while (rg--)
        {
            std::cout << (status? "GR": "RG");
        }
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
