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
    int n, m;
    std::cin >> n >> m;

    int ans = 0;
    for (int i = 0, pre = 0; i < n; ++i)
    {
        int sum = 0;
        for (int i = 0, cur; i < m; ++i)
        {
            std::cin >> cur;

            sum += cur;
        }

        if (sum < pre)
        {
            ++ans;
        }

        pre = sum;
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
