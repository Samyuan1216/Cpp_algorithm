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
    int h, w;
    std::cin >> h >> w;

    std::vector<std::string> g(h);
    for (auto &str: g)
    {
        std::cin >> str;
    }

    auto check = [&](int h1, int w1, int h2, int w2) -> bool
    {
        for (int i = h1; i <= h2; ++i)
        {
            for (int j = w1; j <= w2; ++j)
            {
                if (g[i][j] != g[h1 + h2 - i][w1 + w2 - j])
                {
                    return false;
                }
            }
        }

        return true;
    };

    int ans = 0;
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            for (int s1 = 0; s1 < h; ++s1)
            {
                for (int s2 = 0; s2 < w; ++s2)
                {
                    if (s1 + i >= h || s2 + j >= w)
                    {
                        continue;
                    }

                    if (check(s1, s2, s1 + i, s2 + j))
                    {
                        ++ans;
                    }
                }
            }
        }
    }

    std::cout << ans << "\n";
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
