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

    std::map<std::string, int> mp;
    while (n--)
    {
        std::string str;
        std::cin >> str;

        for (auto &c: str)
        {
            c = std::tolower(c);
        }

        debug(str);

        ++mp[str];
    }

    debug(mp);

    int max = 0;
    for (auto &[key, num]: mp)
    {
        if (num > max)
        {
            max = num;
        }
    }

    std::cout << max << "\n";
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
