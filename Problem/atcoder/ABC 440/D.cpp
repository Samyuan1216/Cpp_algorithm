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
    int n, q;
    std::cin >> n >> q;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    ranges::sort(arr);

    std::vector<int> sum(n);
    sum[0] = arr[0] - 1;

    for (int i = 1; i < n; ++i)
    {
        sum[i] = sum[i - 1] + (arr[i] - arr[i - 1] - 1);
    }

    while (q--)
    {
        int x, y;
        std::cin >> x >> y;

        auto iter1 = ranges::lower_bound(arr, x);
        if (iter1 == arr.end() || *iter1 - x >= y)
        {
            std::cout << x + y - 1 << "\n";
            continue;
        }

        y -= *iter1 - x;
        int i = std::distance(arr.begin(), iter1);

        i64 k = sum[i] + y;
        auto iter2 = ranges::lower_bound(sum, k);

        if (iter2 == sum.end())
        {
            std::cout << arr.back() + (k - sum.back()) << "\n";
            continue;
        }

        int j = std::distance(sum.begin(), iter2);
        std::cout << arr[j] - (sum[j] - k + 1) << "\n";
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    while (t--)
    {
        solve();
    }
}
