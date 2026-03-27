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
    int n, m;
    std::cin >> n >> m;

    i64 r, ansr;
    if (n & 1)
    {
        ansr = ((i64)n * m + 1) / 2;
    }
    else
    {
        r = (n - 1) / 2;
        ansr = (r & 1? ((i64)(r - 1) / 2 * m + m / 2 + (m & 1? 1: 0)) * 2: (i64)r / 2 * m * 2);
    }

    i64 c, ansc;
    if (m & 1)
    {
        ansc = ((i64)n * m + 1) / 2;
    }
    else
    {
        c = (m - 1) / 2;
        ansc = (c & 1? ((i64)(c - 1) / 2 * n + n / 2 + (m & 1? 1: 0)) * 2: (i64)c / 2 * n * 2);
    }

    std::cout << std::max(ansr, ansc) << "\n";
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
