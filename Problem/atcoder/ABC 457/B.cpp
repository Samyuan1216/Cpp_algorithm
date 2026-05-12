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
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> grid(n);
    for (auto &line: grid)
    {
        int l;
        std::cin >> l;

        for (int i = 0, x; i < l; ++i)
        {
            std::cin >> x;

            line.push_back(x);
        }
    }

    int x, y;
    std::cin >> x >> y;
    std::cout << grid[x - 1][y - 1] << "\n";
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
