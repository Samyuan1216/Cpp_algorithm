#include <bits/extc++.h>
namespace ranges = std::ranges;
namespace pbds = __gnu_pbds;

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

    std::vector<i64> a(n);
    for (auto &x: a)
    {
        std::cin >> x;
    }

    std::vector<std::array<i64, 2>> b(n);
    for (int i = 1; i < n; ++i)
    {
        b[i][0] = b[i - 1][0] + a[i - 1];
        b[i][1] = i;
    }

    ranges::sort(b, std::greater());

    std::vector<i64> ans(n);
    for (int i = 0; i < n; ++i)
    {
        ans[b[i][1]] = i + 1;
    }

    for (int i = 0; i < n; ++i)
    {
        std::cout << ans[i] << " \n"[i == n - 1];
    }
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
