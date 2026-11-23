#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

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

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    i64 ans = (arr[n - 1] > 0 ? 1: 0);
    for (int i = n - 2; i >= 0; --i)
    {
        i64 d = arr[i] - 2 * arr[i + 1];
        if (d < 0)
        {
            std::cout << -1 << '\n';
            return;
        }

        ans = std::max(ans, d);
    }

    std::cout << ans << '\n';
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