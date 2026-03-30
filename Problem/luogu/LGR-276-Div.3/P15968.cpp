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
    i64 n, x, y, w;
    std::cin >> n >> x >> y >> w;

    auto arr = std::vector(n, std::array<i64, 2>());
    for (int i = 0; i < n; ++i)
    {
        std::cin >> arr[i][0] >> arr[i][1];
    }

    ranges::sort(arr);

    auto pre = std::vector<i64>(n + 1);
    for (int i = 0; i < n; ++i)
    {
        pre[i + 1] = pre[i] + arr[i][1];
    }

    i64 ans = 0;
    for (int i = 0; i < n; ++i)
    {
        i64 min = (pre[i] + w - 1) / w, max = (pre[i + 1] - 1) / w;
        if (min > max)
        {
            continue;
        }

        ans += (max - min + 1) * 2 * (y - arr[i][0]);
    }

    ans += std::abs(x - arr[0][0]) - (y - arr[0][0]);
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
