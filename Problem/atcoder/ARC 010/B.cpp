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

    std::set<std::array<int, 2>> day;
    for (int i = 0, m, d; i < n; ++i)
    {
        scanf("%d/%d", &m, &d);

        day.insert({m, d});
    }

    auto add = [&](std::array<int, 2> d) -> std::array<int, 2>
    {
        if (d[0] == 2)
        {
            if (d[1] == 29)
            {
                return {3, 1};
            }
            else
            {
                return {2, d[1] + 1};
            }
        }
        else if (std::set{4, 6, 9, 11}.contains(d[0]))
        {
            if (d[1] == 30)
            {
                return {d[0] + 1, 1};
            }
            else
            {
                return {d[0], d[1] + 1};
            }
        }
        else
        {
            if (d[1] == 31)
            {
                return {d[0] + 1, 1};
            }
            else
            {
                return {d[0], d[1] + 1};
            }
        }
    };

    int max = 0;
    for (int i = 0, m = 1, d = 1, w = 0, len = 0, res = 0; i < 366; ++i, w = (w + 1) % 7)
    {
        if (day.contains({m, d}))
        {
            if (w == 0 || w == 6)
            {
                ++res;
            }

            ++len;
        }
        else if (w == 0 || w == 6)
        {
            ++len;
        }
        else if (res > 0)
        {
            --res;
            ++len;
        }
        else
        {
            len = 0;
        }

        max = std::max(max, len);

        auto tmp = add({m, d});
        m = tmp[0], d = tmp[1];
    }

    std::cout << max << "\n";
}

int main()
{
    int t = 1;
    while (t--)
    {
        solve();
    }
}
