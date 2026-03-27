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
    int h, w;
    std::cin >> h >> w;

    int q;
    std::cin >> q;

    while (q--)
    {
        int op, x;
        std::cin >> op >> x;

        if (op == 1)
        {
            std::cout << x * w << "\n";
            h -= x;
        }
        else
        {
            std::cout << x * h << "\n";
            w -= x;
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
