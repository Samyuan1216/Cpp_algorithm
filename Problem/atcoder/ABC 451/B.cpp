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
    int n, m;
    std::cin >> n >> m;

    auto a = std::vector<int>(m + 1), b = std::vector<int>(m + 1);
    for (int i = 0, x, y; i < n; ++i)
    {
        std::cin >> x >> y;

        ++a[x], ++b[y];
    }

    for (int i = 1; i <= m; ++i)
    {
        std::cout << b[i] - a[i] << "\n";
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
