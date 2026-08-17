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
    int h, w, q;
    std::cin >> h >> w >> q;

    std::vector<std::tuple<int, int, char>> op(q);
    for (auto &[r, c, x]: op)
    {
        std::cin >> r >> c >> x;
        --r, --c;
    }

    ranges::reverse(op);

    std::vector g(h, std::vector<char>(w, '0'));
    auto paint = [&](this auto &&self, int x, int y, char c) -> void
    {
        g[x][y] = c;
        if (x > 0 && g[x - 1][y] == '0')
        {
            self(x - 1, y, c);
        }

        if (y > 0 && g[x][y - 1] == '0')
        {
            self(x, y - 1, c);
        }
    };

    for (auto &[r, c, x]: op)
    {
        if (g[r][c] == '0')
        {
            paint(r, c, x);
        }
    }

    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            std::cout << (g[i][j] == '0'? 'A': g[i][j]);
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
