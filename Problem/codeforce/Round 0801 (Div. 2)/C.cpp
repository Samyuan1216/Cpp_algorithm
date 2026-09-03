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
    int n, m;
    std::cin >> n >> m;

    std::vector grid(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            std::cin >> grid[i][j];
        }
    }

    if ((n + m) % 2 == 0)
    {
        std::cout << "NO\n";
        return;
    }

    constexpr int INF = 1e9;
    std::vector max(n, std::vector<int>(m, -INF)), min(n, std::vector<int>(m, INF));
    max[0][0] = min[0][0] = grid[0][0];

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }

            if (i > 0)
            {
                max[i][j] = std::max(max[i][j], max[i - 1][j] + grid[i][j]);
                min[i][j] = std::min(min[i][j], min[i - 1][j] + grid[i][j]);
            }

            if (j > 0)
            {
                max[i][j] = std::max(max[i][j], max[i][j - 1] + grid[i][j]);
                min[i][j] = std::min(min[i][j], min[i][j - 1] + grid[i][j]);
            }
        }
    }

    std::cout << (max[n - 1][m - 1] >= 0 && min[n - 1][m - 1] <= 0? "YES\n": "NO\n");
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    std::cin >> t;
    while (t--)
    {
        solve();
    }
}
