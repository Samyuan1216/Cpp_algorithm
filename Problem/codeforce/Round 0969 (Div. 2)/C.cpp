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
    int n, a, b;
    std::cin >> n >> a >> b;

    int g = std::gcd(a, b);
    std::vector<int> arr(n);

    for (auto &x: arr)
    {
        std::cin >> x;

        x %= g;
    }

    ranges::sort(arr);

    int max = arr[0] + g - arr[n - 1];
    for (int i = 1; i < n; ++i)
    {
        max = std::max(max, arr[i] - arr[i - 1]);
    }

    std::cout << g - max << "\n";
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
