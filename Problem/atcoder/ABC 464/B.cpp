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

    std::vector<std::string> g(h);
    for (auto &str: g)
    {
        std::cin >> str;
    }

    int u = 0;
    for (int i = 0; ; ++i, ++u)
    {
        bool status = false;
        for (int j = 0; j < w; ++j)
        {
            if (g[i][j] == '#')
            {
                status = true;
                break;
            }
        }

        if (status)
        {
            break;
        }
    }

    int d = h - 1;
    for (int i = d; ; --i, --d)
    {
        bool status = false;
        for (int j = 0; j < w; ++j)
        {
            if (g[i][j] == '#')
            {
                status = true;
                break;
            }
        }

        if (status)
        {
            break;
        }
    }

    int l = 0;
    for (int j = 0; ; ++j, ++l)
    {
        bool status = false;
        for (int i = 0; i < h; ++i)
        {
            if (g[i][j] == '#')
            {
                status = true;
                break;
            }
        }

        if (status)
        {
            break;
        }
    }

    int r = w - 1;
    for (int j = r; ; --j, --r)
    {
        bool status = false;
        for (int i = 0; i < h; ++i)
        {
            if (g[i][j] == '#')
            {
                status = true;
                break;
            }
        }

        if (status)
        {
            break;
        }
    }

    for (int i = u; i <= d; ++i)
    {
        for (int j = l; j <= r; ++j)
        {
            std::cout << g[i][j];
        }
        std::cout << "\n";
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
