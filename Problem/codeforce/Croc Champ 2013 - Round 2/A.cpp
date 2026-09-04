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
    std::string s1, s2;
    std::cin >> n >> s1 >> s2;

    int p11 = 0, p10 = 0, p01 = 0, p00 = 0;
    for (int i = 0; i < 2 * n; ++i)
    {
        if (s1[i] == '1' && s2[i] == '1')
        {
            ++p11;
        }
        else if (s1[i] == '1' && s2[i] == '0')
        {
            ++p10;
        }
        else if (s1[i] == '0' && s2[i] == '1')
        {
            ++p01;
        }
        else
        {
            ++p00;
        }
    }

    int f = (p11 + 1) / 2, s = p11 / 2;
    bool first = !(p11 & 1);

    int min = std::min(p10, p01);
    f += min;
    s += min;
    p10 -= min;
    p01 -= min;

    if (p10 > 0)
    {
        f += (first? (p10 + 1) / 2: p10 / 2);
    }

    if (p01 > 0)
    {
        s += (!first? (p01 + 1) / 2: p01 / 2);
    }

    if (f > s)
    {
        std::cout << "First\n";
    }
    else if (f < s)
    {
        std::cout << "Second\n";
    }
    else
    {
        std::cout << "Draw\n";
    }
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
