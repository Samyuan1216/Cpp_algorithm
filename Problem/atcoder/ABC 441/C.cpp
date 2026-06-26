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
    i64 n, k, x;
    std::cin >> n >> k >> x;

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    ranges::sort(arr);

    i64 cnt = n - k;
    for (int i = k - 1; i >= 0 && x > 0; --i)
    {
        x -= arr[i];
        ++cnt;
    }

    std::cout << (x <= 0? cnt: -1) << "\n";
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
