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
    int n, c;
    std::cin >> n >> c;

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;

        x -= c;
    }

    ranges::sort(arr, std::greater());

    i64 ans = 0, cnt = (n + 1) / 2;
    for (int i = 0; i < n; ++i)
    {
        if (i < cnt || arr[i] > 0)
        {
            ans += arr[i];
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
