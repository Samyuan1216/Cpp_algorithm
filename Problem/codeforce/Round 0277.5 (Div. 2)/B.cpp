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
    int n;
    std::cin >> n;

    auto b = std::vector<int>(n);
    for (auto &x: b)
    {
        std::cin >> x;
    }

    int m;
    std::cin >> m;

    auto g = std::vector<int>(m);
    for (auto &x: g)
    {
        std::cin >> x;
    }

    ranges::sort(b);
    ranges::sort(g);

    int ans = 0;
    for (int i = 0, j = 0; i < n && j < m;)
    {
        while (i < n && b[i] < g[j] - 1)
        {
            ++i;
        }

        while (j < m && g[j] < b[i] - 1)
        {
            ++j;
        }

        if (i < n && j < m && std::abs(b[i] - g[j]) <= 1)
        {
            ++ans;
            ++i, ++j;
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
