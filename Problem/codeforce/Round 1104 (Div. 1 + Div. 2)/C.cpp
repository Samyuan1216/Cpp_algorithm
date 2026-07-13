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
    int n;
    std::cin >> n;

    i64 max = 0;
    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;

        if (x >= max)
        {
            max = x;
        }
        else
        {
            max += x;
        }
    }

    std::cout << max << "\n";
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
