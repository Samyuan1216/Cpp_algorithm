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
    int x;
    std::cin >> x;

    bool status = false;
    for (int d = 0; d <= 10; ++d)
    {
        if (x < 111 * d)
        {
            break;
        }

        if ((x - 111 * d) % 11 == 0)
        {
            status = true;
            break;
        }
    }

    std::cout << (status? "YES\n": "NO\n");
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
