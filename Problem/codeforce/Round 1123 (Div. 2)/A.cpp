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
    char c;
    std::string str;
    std::cin >> n >> c >> str;

    int ans = 0;
    for (int l = 0, r = n - 1; l < r; ++l, --r)
    {
        if (str[l] != str[r])
        {
            ans += (str[l] != c) + (str[r] != c);
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
