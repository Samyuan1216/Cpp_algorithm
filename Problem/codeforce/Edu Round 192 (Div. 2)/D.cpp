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
    std::string str1, str2;
    std::cin >> str1 >> str2;

    int n = std::ssize(str1);
    std::vector<int> prea(n + 1);

    for (int i = 0; i < n; ++i)
    {
        prea[i + 1] = (prea[i] + str1[i] - '0') % 10;
    }

    int m = std::ssize(str2);
    std::vector<int> preb(m + 1);

    for (int i = 0; i < m; ++i)
    {
        preb[i + 1] = (preb[i] + str2[i] - '0') % 10;
    }

    auto D = [&](int x, int y) -> int
    {
        return (prea[x] - preb[y] + 10) % 10;
    };

    if (D(n, m) != 0)
    {
        std::cout << -1 << "\n";
        return;
    }

    auto flat_index = [](auto ...D)
    {
        return [=](auto ...i)
        {
            int idx = 0;
            ((idx = idx * D + i), ...);
    
            return idx;
        };
    };
    auto idx1 = flat_index(n + 1, m + 1), idx2 = flat_index(10, m + 1);

    std::vector<int> dp((n + 1) * (m + 1), -1), max(10 * (m + 1), -1);
    dp[idx1(0, 0)] = 0;

    for (int x = 0; x <= n; ++x)
    {
        if (x > 0)
        {
            for (int y = 0; y <= m; ++y)
            {
                if (y > 0 && max[idx2(D(x, y), y - 1)] != -1)
                {
                    dp[idx1(x, y)] = max[idx2(D(x, y), y - 1)] + 1;
                }
            }
        }

        for (int r = 0, cur; r < 10; ++r)
        {
            cur = -1;
            for (int y = 0; y <= m; ++y)
            {
                if (D(x, y) == r)
                {
                    cur = std::max(cur, dp[idx1(x, y)]);
                }

                max[idx2(r, y)] = std::max(max[idx2(r, y)], cur);
            }
        }
    }

    std::cout << dp[idx1(n, m)] << "\n";
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
