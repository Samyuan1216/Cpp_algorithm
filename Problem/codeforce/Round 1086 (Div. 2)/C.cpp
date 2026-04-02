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

    auto c = std::vector<int>(n), p = std::vector<int>(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> c[i] >> p[i];
    }

    double ans = 0;
    for (int i = n - 1; i >= 0; --i)
    {
        ans = std::max(ans, c[i] + ans * (1.0 - p[i] / 100.0));
    }

    std::cout << std::format("{}\n", ans);
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
