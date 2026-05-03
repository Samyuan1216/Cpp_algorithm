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
    constexpr int mod = 998244353;

    std::string str;
    std::cin >> str;

    int ans = 0;
    for (int i = 0, len = 1; i < std::ssize(str); ++i, ++len)
    {
        if (i > 0 && str[i] == str[i - 1])
        {
            len = 1;
        }

        ans = (ans + len) % mod;
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
