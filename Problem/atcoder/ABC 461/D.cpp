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
    int h, w, k;
    std::cin >> h >> w >> k;

    std::vector<std::string> grid(h);
    for (auto &str: grid)
    {
        std::cin >> str;
    }

    auto sum = std::vector(h + 1, std::vector<i64>(w + 1));
    for (int i = 1; i <= h; ++i)
    {
        for (int j = 1; j <= w; ++j)
        {
            sum[i][j] += (grid[i - 1][j - 1] - '0') + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }

    i64 ans = 0;
    for (int i = 1; i <= h; ++i)
    {
        for (int j = i; j <= h; ++j)
        {
            auto get_sum = [&](int col) -> i64
            {
                return sum[j][col] - sum[i - 1][col];
            };

            for (int l1 = 0, l2 = 0, r = 1; r <= w; ++r)
            {
                while (l1 < r && get_sum(r) - get_sum(l1) > k)
                {
                    ++l1;
                }

                while (l2 < r && get_sum(r) - get_sum(l2) >= k)
                {
                    ++l2;
                }

                ans += l2 - l1;
            }
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
