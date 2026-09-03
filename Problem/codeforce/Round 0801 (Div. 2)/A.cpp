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
    i64 n, m;
    std::cin >> n >> m;

    std::vector grid(n, std::vector<i64>(m));
    i64 max = -1e9, x, y;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            std::cin >> grid[i][j];

            if (grid[i][j] > max)
            {
                max = grid[i][j];
                x = i, y = j;
            }
        }
    }

    std::cout << std::max(x + 1, n - x) * std::max(y + 1, m - y) << "\n";
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
