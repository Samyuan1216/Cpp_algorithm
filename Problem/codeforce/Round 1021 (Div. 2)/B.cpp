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
    int n, k;
    std::cin >> n >> k;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    ranges::sort(arr);

    int l = (n - 1) / 2, r = n / 2;
    if (k == 0)
    {
        std::cout << arr[r] - arr[l] + 1 << "\n";
        return;
    }

    if (n & 1)
    {
        --l, ++r;
        --k;
    }

    while (k > 1)
    {
        --l, ++r;
        k -= 2;
    }

    std::cout << arr[r] - arr[l] + 1 << "\n";
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
