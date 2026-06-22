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
    int a, b, x;
    std::cin >> a >> b >> x;

    if (a < b)
    {
        std::swap(a, b);
    }

    int ans = a - b, cnt = 0;
    while (a != 0 || b != 0)
    {
        ans = std::min(ans, cnt + a - b);
        a /= x;
        ++cnt;

        if (a < b)
        {
            std::swap(a, b);
        }
    }

    ans = std::min(ans, cnt);
    std::cout << ans << "\n";
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
