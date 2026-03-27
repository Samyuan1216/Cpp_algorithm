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
    int n, k;
    std::cin >> n >> k;

    auto a = std::vector<int>(n);
    for (auto &x: a)
    {
        std::cin >> x;

        x %= k;
    }

    ranges::sort(a);

    int ans = a.back() - a.front();
    for (int i = 1; i < n; ++i)
    {
        ans = std::min(ans, a[i - 1] + k - a[i]);
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
