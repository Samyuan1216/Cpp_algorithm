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

    auto query = [&](int l, int r) -> bool
    {
        std::cout << std::format("? {} {}", l, r) << std::endl;

        std::string str;
        std::cin >> str;

        return str == "Yes";
    };

    i64 ans = 0;
    for (int l = 1, r = 2; r <= n; ++r)
    {
        while (l < r)
        {
            if (query(l, r))
            {
                ans += r - l;
                break;
            }

            ++l;
        }
    }

    std::cout << std::format("! {}", ans) << std::endl;
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
