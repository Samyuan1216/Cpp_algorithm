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

    if (n == 2)
    {
        std::cout << -1 << "\n";
        return;
    }

    std::vector<i64> ans(std::max(n, 2));
    ans[0] = 1, ans[1] = 2;

    for (i64 i = 2, sum = 3; i < n; ++i)
    {
        ans[i] = sum;
        sum += ans[i];
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
