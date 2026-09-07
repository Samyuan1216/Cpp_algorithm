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
    int n, m;
    std::cin >> n >> m;

    int x = -2e9;
    for (int i = 0, t; i < n; ++i)
    {
        std::cin >> t;

        x = std::max(x, t);
    }

    while (m--)
    {
        char op;
        int l, r;
        std::cin >> op >> l >> r;

        if (l > x || r < x)
        {
            std::cout << x << " \n"[m == 0];
            continue;
        }

        if (op == '+')
        {
            ++x;
        }
        else
        {
            --x;
        }

        std::cout << x << " \n"[m == 0];
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
