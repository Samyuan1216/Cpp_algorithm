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

    auto p = std::vector<i64>(n, n - 1);
    for (int i = 0, a, b; i < m; ++i)
    {
        std::cin >> a >> b;

        --p[a - 1], --p[b - 1];
    }

    for (int i = 0; i < n; ++i)
    {
        std::cout << (p[i] * (p[i] - 1) * (p[i] - 2)) / 6 << " \n"[i == n - 1];
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
