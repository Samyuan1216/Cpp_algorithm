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

    std::vector<int> a(n);
    for (auto &x: a)
    {
        std::cin >> x;
    }

    i64 sum1 = 0;
    for (int i = 0; i < n; ++i)
    {
        if (i < n - 1)
        {
            sum1 += a[i] - (a[i + 1] - 1);
        }
        else
        {
            sum1 += a[i];
        }
    }

    std::vector<int> b(m);
    for (auto &x: b)
    {
        std::cin >> x;
    }

    i64 sum2 = 0;
    for (int i = 0; i < m; ++i)
    {
        if (i < m - 1)
        {
            sum2 += b[i] - (b[i + 1] - 1);
        }
        else
        {
            sum2 += b[i];
        }
    }

    std::cout << (sum1 >= sum2? 1: 2) << "\n";
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
