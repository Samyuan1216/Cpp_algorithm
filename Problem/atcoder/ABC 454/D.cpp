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
    std::string a, b;
    std::cin >> a >> b;

    auto compute = [](std::string &str) -> void
    {
        for (int i = 0, j = 1; j < std::ssize(str); ++i, ++j)
        {
            if (str[i] == 'x' && str[j] == 'x')
            {
                int l = i - 1, r = j + 1;
                while (l >= 0 && r < std::ssize(str) && str[l] == '(' && str[r] == ')')
                {
                    str[l] = str[r] = '#';
                    --l, ++r;
                }
            }
        }
    };

    compute(a), compute(b);

    std::string resa;
    for (auto &c: a)
    {
        if (c == '#')
        {
            continue;
        }

        resa += c;
    }

    std::string resb;
    for (auto &c: b)
    {
        if (c == '#')
        {
            continue;
        }

        resb += c;
    }

    std::cout << (resa == resb? "Yes\n": "No\n");
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
