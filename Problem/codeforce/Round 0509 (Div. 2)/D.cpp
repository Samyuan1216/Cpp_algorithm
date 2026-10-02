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
    i64 n, h;
    std::cin >> n >> h;

    std::vector<std::array<i64, 2>> lines(n);
    for (auto &[x, y]: lines)
    {
        std::cin >> x >> y;
    }

    std::vector<i64> pre(n);
    pre[0] = lines[0][0];

    for (int i = 1; i < n; ++i)
    {
        pre[i] = pre[i - 1] + (lines[i][0] - lines[i - 1][1]);
    }

    i64 ans = h;
    for (int i = 0; i < n; ++i)
    {
        i64 t = pre[i] - (h - 1), s;
        if (t <= pre[0])
        {
            s = t;
        }
        else
        {
            int j = std::distance(pre.begin(), ranges::lower_bound(pre.begin(), pre.begin() + i + 1, t));
            s = lines[j - 1][1] + (t - pre[j - 1]);
        }

        ans = std::max(ans, lines[i][1] + 1 - s);
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
