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

    std::array<int, 2> s, t;
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            if (grid[i][j] == 'S')
            {
                s = {i, j};
            }
            else if (grid[i][j] == 'T')
            {
                t = {i, j};
            }
        }
    }

    std::queue<std::array<int, 3>> q;
    std::map<std::array<int, 2>, int> mp;

    int n;
    std::cin >> n;

    for (int i = 0, r, c, e; i < n; ++i)
    {
        std::cin >> r >> c >> e;
        --r, --c;

        if (s == std::array{r, c})
        {
            q.push({r, c, e});
        }
        else
        {
            mp[{r, c}] = e;
        }
    }

    std::array dx = {-1, 1, 0, 0}, dy = {0, 0, -1, 1};
    auto bfs = [&](std::array<int, 3> st) -> bool
    {
        std::queue<std::array<int, 3>> tq;
        tq.push(st);

        std::vector vis(h, std::vector<bool>(w));
        while (!tq.empty())
        {
            auto [r, c, e] = tq.front();
            tq.pop();

            if (mp.contains({r, c}))
            {
                q.push({r, c, mp[{r, c}]});
                mp.erase({r, c});
            }

            if (t == std::array{r, c})
            {
                return true;
            }

            if (e == 0)
            {
                continue;
            }

            for (int i = 0, nx, ny; i < 4; ++i)
            {
                nx = r + dx[i], ny = c + dy[i];
                if (nx < 0 || ny < 0 || nx >= h || ny >= w || grid[nx][ny] == '#' || vis[nx][ny])
                {
                    continue;
                }

                tq.push({nx, ny, e - 1});
                vis[nx][ny] = true;
            }
        }

        return false;
    };

    while (!q.empty())
    {
        auto p = q.front();
        q.pop();

        if (bfs(p))
        {
            std::cout << "Yes\n";
            return;
        }
    }

    std::cout << "No\n";
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
