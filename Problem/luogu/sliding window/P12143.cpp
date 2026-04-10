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
    auto str = std::string();
    std::cin >> str;

    i64 ans = 0;
    for (int l = 0, r = 0, cnt = 0; r < std::ssize(str); ++r)
    {
        if (r > 0 && str[r] != str[r - 1] && str[r] != str[r - 1] + 1)
        {
            ++cnt;
        }

        while (cnt > 1)
        {
            ++l;
            if (str[l] != str[l - 1] && str[l] != str[l - 1] + 1)
            {
                --cnt;
            }
        }

        ans += r - l + 1;
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
