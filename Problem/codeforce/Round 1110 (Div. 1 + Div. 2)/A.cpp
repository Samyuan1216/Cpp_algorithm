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
    int n, k;
    std::string str;
    std::cin >> n >> k >> str;

    if (n < 2 * k)
    {
        std::cout << -1 << "\n";
        return;
    }

    int ans = 0;
    for (int i = 0; i < k; ++i)
    {
        if (str[i] == 'L')
        {
            ++ans;
        }
    }

    for (int i = n - 1; i >= n - k; --i)
    {
        if (str[i] == 'R')
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
