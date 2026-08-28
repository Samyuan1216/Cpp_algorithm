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
    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    int sum = 0;

    for (auto &x: arr)
    {
        std::cin >> x;

        sum += x;
    }

    int ans = 1e9;
    for (int i = 0, pre = 0; i < n - 1; ++i)
    {
        pre += arr[i];
        ans = std::min(ans, std::abs(pre - (sum - pre)));
    }

    std::cout << ans << "\n";
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
