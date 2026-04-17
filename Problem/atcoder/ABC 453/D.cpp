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
    int sx, sy, ex, ey;
    for (int i = 0; i < h; ++i)
    {
        std::cin >> g[i];

        for (int j = 0; j < w; ++j)
        {
            if (g[i][j] == 'S')
            {
                sx = i, sy = j;
            }
            else if (g[i][j] == 'G')
            {
                ex = i, ey = j;
            }
        }
    }

    auto visited = std::vector(h, std::vector(w, std::array<bool, 4>()));
    auto dist = std::array{-1, 0, 1, 0, -1};
    std::string ans, path, str = "URDL";

    [&](this auto &&self, int x, int y, int i) -> void
    {
        visited[x][y][i] = true;
        if (x == ex && y == ey)
        {
            ans = path;
            return;
        }

        for (int j = 0, nx, ny; j < 4; ++j)
        {
            nx = x + dist[j], ny = y + dist[j + 1];
            if (nx < 0 || nx >= h || ny < 0 || ny >= w || visited[nx][ny][j] || g[nx][ny] == '#' || (g[x][y] == 'o' && i != j) || (g[x][y] == 'x' && i == j))
            {
                continue;
            }

            path.push_back(str[j]);
            self(nx, ny, j);
            path.pop_back();
        }
    } (sx, sy, 0);

    if (ans.empty())
    {
        std::cout << "No\n";
    }
    else
    {
        std::cout << "Yes\n";
        std::cout << ans << "\n";
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
