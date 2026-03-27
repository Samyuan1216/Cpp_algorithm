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

    auto g = std::vector<std::string>(h);
    for (auto &str: g)
    {
        std::cin >> str;
    }

    auto visited = std::vector(h, std::vector<bool>(w));
    auto dist = std::vector{-1, 0, 1, 0, -1};
    auto dfs = [&](this auto &&self, int x, int y) -> bool
    {
        visited[x][y] = true;
        if (x == 0 || x == h - 1 || y == 0 || y == w - 1)
        {
            return false;
        }

        bool status = true;
        for (int i = 0; i < 4; ++i)
        {
            int vx = x + dist[i], vy = y + dist[i + 1];
            if (g[vx][vy] == '.' && !visited[vx][vy])
            {
                status = self(vx, vy) && status;
            }
        }

        return status;
    };

    int ans = 0;
    for (int i = 1; i < h - 1; ++i)
    {
        for (int j = 1; j < w - 1; ++j)
        {
            if (g[i][j] == '.' && !visited[i][j] && dfs(i, j))
            {
                ++ans;
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
