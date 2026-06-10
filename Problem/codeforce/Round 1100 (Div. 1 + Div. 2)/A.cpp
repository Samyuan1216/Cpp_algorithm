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

    int max = 0, min = 1000;
    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;

        max = std::max(max, x);
        min = std::min(min, x);
    }

    int mid = (max + min) / 2;
    std::cout << std::max(mid - min, max - mid) << "\n";
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
