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

    std::vector<std::string> grid(h);
    for (auto &str: grid)
    {
        std::cin >> str;
    }

    std::vector<std::array<int, 2>> dir{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    auto ans = grid;
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            if (grid[i][j] == '#')
            {
                ans[i][j] = '.';
                continue;
            }

            for (auto &[dx, dy]: dir)
            {
                if (i + dx < 0 || i + dx >= h || j + dy < 0 || j + dy >= w)
                {
                    continue;
                }

                if (grid[i + dx][j + dy] == '#')
                {
                    ans[i][j] = '#';
                    break;
                }
            }
        }
    }

    grid = ans;
    debug(grid);
    
    auto dist = std::vector(h, std::vector<int>(w, -1));
    [&]() -> void
    {
        std::queue<std::array<int, 3>> q;
        for (int i = 0; i < h; ++i)
        {
            for (int j = 0; j < w; ++j)
            {
                if (grid[i][j] == '#')
                {
                    q.push({i, j, 0});
                }
            }
        }

        while (!q.empty())
        {
            auto [x, y, d] = q.front();
            q.pop();

            if (dist[x][y] >= 0)
            {
                continue;
            }

            dist[x][y] = d;
            for (auto &[dx, dy]: dir)
            {
                if (x + dx < 0 || x + dx >= h || y + dy < 0 || y + dy >= w)
                {
                    continue;
                }

                q.push({x + dx, y + dy, d + 1});
            }
        }
    } ();

    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            if (dist[i][j] == -1 || dist[i][j] % 2 == 0)
            {
                std::cout << ".";
            }
            else
            {
                std::cout << "#";
            }
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
