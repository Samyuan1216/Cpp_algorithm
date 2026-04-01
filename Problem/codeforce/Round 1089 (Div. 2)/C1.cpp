#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

template<typename T>
using lim = std::numeric_limits<T>;

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

    auto a = std::vector<int>(n);
    for (auto &x: a)
    {
        std::cin >> x;
    }

    auto b = std::vector<int>(n);
    for (auto &x: b)
    {
        std::cin >> x;
    }

    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        int g = 0;
        if (i >= 1)
        {
            g = a[i] / std::gcd(a[i - 1], a[i]);
        }

        if (i < n - 1)
        {
            int num = a[i] / std::gcd(a[i], a[i + 1]);
            g = (g == 0? num: std::gcd(g, num));
        }

        if (g > 1)
        {
            ++ans;
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
