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
    std::string str;
    std::cin >> n >> str;

    std::array<bool, 4> limit;
    ranges::fill(limit, true);

    auto check = [&](char c) -> void
    {
        if (c == '1' || c == '2' || c == '3')
        {
            limit[0] = false;
        }

        if (c == '0' || c == '7' || c == '9')
        {
            limit[1] = false;
        }

        if (c == '0' || c == '1' || c == '4' || c == '7')
        {
            limit[2] = false;
        }

        if (c == '0' || c == '3' || c == '6' || c == '9')
        {
            limit[3] = false;
        }
    };

    for (auto &c: str)
    {
        check(c);
    }

    std::cout << (ranges::count(limit, true) == 0? "YES\n": "NO\n");
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
