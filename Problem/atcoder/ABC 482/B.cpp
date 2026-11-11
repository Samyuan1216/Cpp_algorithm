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
    std::vector<std::string> grid(5);
    for (auto &s: grid)
    {
        std::cin >> s;
    }

    int min = 5;
    for (int i = 0; i < 5; ++i)
    {
        int cnt = 0;
        for (int j = 0; j < 5; ++j)
        {
            if (grid[i][j] == '.')
            {
                ++cnt;
            }
        }

        min = std::min(min, cnt);
    }

    for (int j = 0; j < 5; ++j)
    {
        int cnt = 0;
        for (int i = 0; i < 5; ++i)
        {
            if (grid[i][j] == '.')
            {
                ++cnt;
            }
        }

        min = std::min(min, cnt);
    }

    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < 5; ++i)
    {
        if (grid[i][i] == '.')
        {
            ++cnt1;
        }

        if (grid[i][4 - i] == '.')
        {
            ++cnt2;
        }
    }

    std::cout << std::min({min, cnt1, cnt2}) << "\n";
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