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
    i64 t, h, u;
    std::cin >> t >> h >> u;

    i64 n = 0, cnt = 0;

    cnt = std::min(t, u);
    n += 4 * cnt;
    t -= cnt;
    u -= cnt;

    cnt = std::min(t / 2, h);
    n += 7 * cnt;
    t -= 2 * cnt;
    h -= cnt;

    cnt = std::min(t, h);
    n += 5 * cnt;
    t -= cnt;
    h -= cnt;

    if (t > 0)
    {
        cnt = t - 1;
        n += 3 + 2 * cnt;
        t = 0;
    }

    cnt = h;
    n += 3 * cnt;
    h -= cnt;

    cnt = u;
    n += 3 * cnt;
    u -= cnt;

    std::cout << n << "\n";
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
