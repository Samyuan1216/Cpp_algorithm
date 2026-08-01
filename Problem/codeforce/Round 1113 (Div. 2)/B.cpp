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

    std::vector<int> a(n), b(m);
    for (auto &x: a)
    {
        std::cin >> x;
    }

    for (auto &x: b)
    {
        std::cin >> x;
    }

    if (n < 2 * m)
    {
        std::cout << "NO\n";
        return;
    }

    ranges::sort(a);
    ranges::sort(b);

    for (int j = 0; j < m; ++j)
    {
        if (a[j] >= b[j])
        {
            std::cout << "NO\n";
            return;
        }

        if (a[n - m + j] <= b[j])
        {
            std::cout << "NO\n";
            return;
        }
    }

    std::cout << "YES\n";
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
