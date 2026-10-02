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

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    i64 ans = 0;
    if (2 * k <= n)
    {
        for (int i = k - 1; i <= n - k; ++i)
        {
            ans += arr[i];
        }

        for (int i = 0; i < k - 1; ++i)
        {
            ans += std::max(arr[i], arr[n - i - 1]);
        }
    }
    else
    {
        for (int i = 0; i <= n - k; ++i)
        {
            ans += std::max(arr[i], arr[n - i - 1]);
        }
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
