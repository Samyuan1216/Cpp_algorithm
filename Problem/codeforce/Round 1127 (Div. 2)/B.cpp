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

    i64 smax = arr[0], smin = arr[0], max = arr[0];
    for (int i = 1; i < n; ++i)
    {
        max = std::max({max, arr[i] + smax, arr[i], arr[i] - smin});
        std::tie(smax, smin) = std::tuple(arr[i] + std::max(0LL, 2 * smax), arr[i] + std::min(0LL, 2 * smin));
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
