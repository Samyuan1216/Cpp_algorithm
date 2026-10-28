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

    ranges::sort(arr);

    int idx = -1, max = 0;
    for (int i = 1; i < n - 1; ++i)
    {
        auto iter = std::prev(ranges::lower_bound(arr, arr[i] + arr[i - 1]));
        int len = std::max(0, int(std::distance(arr.begin(), iter) - (i - 1) + 1));

        if (max < len && len >= 3)
        {
            idx = i;
            max = len;
        }
    }

    if (idx == -1)
    {
        std::cout << 0 << "\n";
        return;
    }

    std::cout << max;
    for (int i = idx - 1, j = 0; j < max; ++i, ++j)
    {
        std::cout << " " << arr[i];
    }
    std::cout << "\n";
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
