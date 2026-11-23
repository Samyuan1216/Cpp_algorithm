#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

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
    int x;
    std::cin >> x;

    auto build = [](int k, int t) -> std::string
    {
        std::string s;
        for (int i = 0; i < k; ++i)
        {
            s += "AR";
        }

        for (int i = 1; i < t; ++i)
        {
            s += "CR";
        }

        s += 'C';
        return s;
    };

    std::string str = build(24, 25);
    for (int rem = 600; rem > x; --rem)
    {
        auto pos = str.find("ARC");
        std::swap(str[pos], str[pos + 2]);
    }

    std::cout << str << "\n";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    // std::cin >> t;
    while (t--)
    {
        solve();
    }
}