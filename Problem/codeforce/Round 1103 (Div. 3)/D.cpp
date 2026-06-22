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

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    ranges::sort(arr);

    for (int i = 0, prev = -1, cnt = 1; i < n; ++i, ++cnt)
    {
        if (i > 0 && arr[i] != arr[i - 1])
        {
            prev = arr[i - 1];
            cnt = 1;
        }

        if (i < n - 1 && std::abs(arr[i + 1] - arr[i]) <= k)
        {
            continue;
        }

        if (cnt % 2 == 0 || (prev != -1 && std::abs(prev - arr[i]) <= k))
        {
            std::cout << "YES\n";
            return;
        }
    }

    std::cout << "NO\n";
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
