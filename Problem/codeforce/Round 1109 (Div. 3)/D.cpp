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

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    std::vector<int> pos(m);
    for (auto &x: pos)
    {
        std::cin >> x;
    }

    ranges::sort(pos);

    int i = 0;
    i64 ans = 0;

    for (auto &x: pos)
    {
        i64 sum = 0;
        for (; i < x; ++i)
        {
            sum += arr[i];
        }

        ans += std::abs(sum);
    }

    for (; i < n; ++i)
    {
        ans += arr[i];
    }

    std::cout << ans << "\n";
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
