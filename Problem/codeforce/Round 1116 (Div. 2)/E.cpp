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

void solve1()
{
    int n;
    std::cin >> n;

    std::vector<std::string> grid(n);
    for (auto &str: grid)
    {
        std::cin >> str;
    }

    int w = 0, sx = 0, sy = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (grid[i][j] == '#')
            {
                ++w;
                sx += i;
                sy += j;
            }
        }
    }

    int xx, xy;
    std::cin >> xx >> xy;
    --xx, --xy;

    int dx = ((w * xx - sx) % n + n) % n, dy = ((w * xy - sy) % n + n) % n;
    if (dx == 0 && dy == 0)
    {
        std::cout << "1 1 1 1\n";
        return;
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (grid[i][j] != '#')
            {
                continue;
            }

            int qx = (dx + i) % n, qy = (dy + j) % n;
            if (grid[qx][qy] == '.')
            {
                std::cout << std::format("{} {} {} {}\n", i + 1, j + 1, qx + 1, qy + 1);
                return;
            }
        }
    }
}

void solve2()
{
    int n;
    std::cin >> n;

    std::vector<std::string> grid(n);
    for (auto &str: grid)
    {
        std::cin >> str;
    }

    int w = 0, sx = 0, sy = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (grid[i][j] == '#')
            {
                ++w;
                sx += i;
                sy += j;
            }
        }
    }

    for (int inv = 1; inv < n; ++inv)
    {
        if (w * inv % n == 1)
        {
            std::cout << (1ll * sx * inv) % n + 1 << " " << (1ll * sy * inv) % n + 1 << "\n";
            return;
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string str;
    std::cin >> str;

    int t = 1;
    std::cin >> t;
    while (t--)
    {
        if (str[0] == 'f')
        {
            solve1();
        }
        else
        {
            solve2();
        }
    }
}
