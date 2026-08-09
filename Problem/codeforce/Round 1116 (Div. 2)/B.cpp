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

    std::string s1;
    for (int i = 0; i <= n / 4; ++i)
    {
        s1 += "0011";
    }

    for (int i = 0; i < 4 - n % 4; ++i)
    {
        s1.pop_back();
    }

    std::string s2 = "0";
    for (int i = 0; i <= (n - 1) / 4; ++i)
    {
        s2 += "1100";
    }

    for (int i = 0; i < 4 - (n - 1) % 4; ++i)
    {
        s2.pop_back();
    }

    std::string s3;
    for (int i = 0; i <= n / 4; ++i)
    {
        s3 += "1100";
    }

    for (int i = 0; i < 4 - n % 4; ++i)
    {
        s3.pop_back();
    }

    std::string s4 = "1";
    for (int i = 0; i <= (n - 1) / 4; ++i)
    {
        s4 += "0011";
    }

    for (int i = 0; i < 4 - (n - 1) % 4; ++i)
    {
        s4.pop_back();
    }

    auto check = [&](std::string &s) -> bool
    {
        for (int i = 0; i < n; ++i)
        {
            if (str[i] != '?' && s[i] != str[i])
            {
                return false;
            }
        }

        return true;
    };

    std::cout << check(s1) + check(s2) + check(s3) + check(s4) << "\n";
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
