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
    int n, k;
    std::cin >> n >> k;

    if (k > 0 && n < k + 2)
    {
        std::cout << -1 << "\n";
        return;
    }

    std::string ans;
    ans += std::string(k / 2 + 1, '0') + std::string(k - k / 2 + 1, '1');

    n -= k + 2;
    for (int i = 0; i < n / 2; ++i)
    {
        ans += "01";
    }

    if (n & 1)
    {
        ans += "0";
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
