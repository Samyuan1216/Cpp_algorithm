#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = int64_t;

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
    int n, m, q;
    std::cin >> n >> m >> q;

    auto arr = std::vector<i64>(n + 1, 1);
    while (m--)
    {
        int x, y, g;
        std::cin >> x >> y >> g;

        if (arr[x] == 0)
        {
            arr[x] = g;
        }
        else
        {
            arr[x] = std::lcm(arr[x], g);
        }

        if (arr[y] == 0)
        {
            arr[y] = g;
        }
        else
        {
            arr[y] = std::lcm(arr[y], g);
        }
    }

    while (q--)
    {
        int x, y;
        std::cin >> x >> y;
        std::cout << std::gcd(arr[x], arr[y]) << "\n";
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
