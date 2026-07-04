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
    i64 n, k;
    std::cin >> n >> k;

    i64 ans = 0, weight = 1;
    while (n > 0 && weight <= n)
    {
        i64 cnt = std::min(k, n / weight);
        ans += cnt;
        n -= cnt * weight;
        weight <<= 1;
    }

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
