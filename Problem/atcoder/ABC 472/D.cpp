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
    int h, w, k;
    std::cin >> h >> w >> k;

    std::vector<std::string> g(h);
    for (auto &str: g)
    {
        std::cin >> str;
    }

    std::vector<bool> row(h, true), col(w, true);
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            if (g[i][j] == '#')
            {
                row[i] = col[j] = false;
            }
        }
    }

    constexpr std::array<int, 4> dx = {-1, 1, 0, 0}, dy = {0, 0, -1, 1};
    std::vector visited(h, std::vector<bool>(w));

    std::queue<std::array<int, 3>> q;
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            if (row[i] && col[j])
            {
                q.push({i, j, 0});
                visited[i][j] = true;
            }
        }
    }

    int ans = 0;
    while (!q.empty())
    {
        auto [x, y, level] = q.front();
        q.pop();

        ++ans;
        if (level == k)
        {
            continue;
        }

        for (int i = 0, nx, ny; i < 4; ++i)
        {
            nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= h || ny < 0 || ny >= w || visited[nx][ny] || g[nx][ny] == '#')
            {
                continue;
            }

            q.push({nx, ny, level + 1});
            visited[nx][ny] = true;
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
