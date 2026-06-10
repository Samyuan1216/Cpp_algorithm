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
    int n;
    std::cin >> n;

    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> a[i] >> b[i];
    }

    std::vector<int> ord(n);
    ranges::iota(ord, 0);

    ranges::sort(ord, {}, [&](int i) { return std::pair{a[i], -b[i]}; });

    std::vector<int> dp;
    for (auto &i: ord)
    {
        auto iter = ranges::lower_bound(dp, b[i]);
        if (iter == dp.end())
        {
            dp.push_back(b[i]);
        }
        else
        {
            *iter = b[i];
        }
    }

    std::cout << dp.size() << "\n";
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
