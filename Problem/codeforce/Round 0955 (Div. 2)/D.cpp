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
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector grid(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            std::cin >> grid[i][j];
        }
    }

    std::vector<std::string> status(n);
    for (auto &str: status)
    {
        std::cin >> str;
    }

    std::vector pre(n + 1, std::vector<int>(m + 1));
    i64 sum1 = 0, sum2 = 0;

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + (status[i - 1][j - 1] == '1'? 1: -1);
            (status[i - 1][j - 1] == '1'? sum1: sum2) += grid[i - 1][j - 1];
        }
    }

    std::set<int> s;
    for (int i = k; i <= n; ++i)
    {
        for (int j = k; j <= m; ++j)
        {
            s.insert(std::abs(pre[i][j] - pre[i - k][j] - pre[i][j - k] + pre[i - k][j - k]));
        }
    }

    s.erase(0);

    if (s.empty())
    {
        std::cout << (sum1 == sum2? "YES\n": "NO\n");
        return;
    }

    int g = *s.begin();
    for (auto &x: s)
    {
        g = std::gcd(g, x);
    }

    std::cout << (std::abs(sum1 - sum2) % g == 0? "YES\n": "NO\n");
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
