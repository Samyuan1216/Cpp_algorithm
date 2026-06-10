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
    int h, w;
    std::cin >> h >> w;

    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            int cnt;
            if (h == 1 && w == 1)
            {
                cnt = 2;
            }
            else if (h == 1 || w == 1)
            {
                cnt = 3;
            }
            else
            {
                cnt = 4;
            }

            if (i == 0 || i == h - 1)
            {
                --cnt;
            }

            if (j == 0 || j == w - 1)
            {
                --cnt;
            }

            std::cout << cnt << " \n"[j == w - 1];
        }
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
