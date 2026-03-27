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
    i64 n, c, k;
    std::cin >> n >> c >> k;

    auto arr = std::vector<i64>(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    ranges::sort(arr);

    for (auto &x: arr)
    {
        if (c < x)
        {
            break;
        }

        i64 add = std::min(k, c - x);
        c += x + add;
        k -= add;
    }

    std::cout << c << "\n";
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
