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
    std::string str;
    int k;
    std::cin >> str >> k;

    int n = std::ssize(str);
    std::vector<int> z(n + 1);

    for (int i = 3; i <= n; ++i)
    {
        if (str[i - 3] == 'A' && str[i - 2] == 'B' && str[i - 1] == 'C')
        {
            z[i] = 1;
        }
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
    auto idx = flat_index(n + 1, k + 2);

    constexpr int INF = 1e9;
    std::vector<int> dp((n + 1) * (k + 2), INF);

    for (int i = 0; i <= n; ++i)
    {
        dp[idx(i, 0)] = 0;
    }

    for (int i = 1; i <= n; ++i)
    {
        int x = 0, y = INF;
        if (i >= 3)
        {
            x = z[i - 2] + z[i - 1] + z[i];
            y = (str[i - 3] != 'A'? 1: 0) + (str[i - 2] != 'B'? 1: 0) + (str[i - 1] != 'C'? 1: 0);
        }

        for (int j = 1; j <= k + 1; ++j)
        {
            if (j + z[i] <= k + 1)
            {
                dp[idx(i, j)] = std::min(dp[idx(i, j)], dp[idx(i - 1, j + z[i])]);
            }

            if (i >= 3)
            {
                if (j + x - 1 >= 0 && j + x - 1 <= k + 1)
                {
                    dp[idx(i, j)] = std::min(dp[idx(i, j)], dp[idx(i - 3, j + x - 1)] + y);
                }
            }
        }
    }

    std::cout << (dp[idx(n, k)] == INF? -1: dp[idx(n, k)]) << "\n";
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
