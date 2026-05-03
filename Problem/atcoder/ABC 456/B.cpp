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
    std::array<std::array<int, 3>, 3> a{};
    for (int i = 0, x; i < 3; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            std::cin >> x;

            if (x >= 4 && x <= 6)
            {
                ++a[i][x - 4];
            }
        }
    }

    int cnt = 0;
    auto dfs = [&](this auto &&dfs, int status, int i, int sum) -> void
    {
        if (i == 3)
        {
            cnt += sum;
            return;
        }

        for (int j = 0; j < 3; ++j)
        {
            if ((status >> j) & 1)
            {
                continue;
            }

            dfs(status | (1 << j), i + 1, sum * a[i][j]);
        }
    };

    for (int i = 0; i < 3; ++i)
    {
        dfs(1 << i, 1, a[0][i]);
    }

    std::cout << std::format("{}\n", double(cnt) / 216.0);
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
