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

    std::vector<std::array<int, 2>> points(n);
    for (auto &[x, y]: points)
    {
        std::cin >> x >> y;
    }

    ranges::sort(points);

    int cnt = 1;
    for (int i = 1, prev = points[0][1]; i < n; ++i)
    {
        if (points[i][1] > prev)
        {
            continue;
        }

        ++cnt;
        prev = points[i][1];
    }

    std::cout << cnt << "\n";
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
