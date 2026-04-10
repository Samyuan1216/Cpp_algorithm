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
    int n;
    std::cin >> n;

    auto a = std::vector<int>(n);
    for (auto &x: a)
    {
        std::cin >> x;
    }

    auto b = std::vector<int>(n);
    for (auto &x: b)
    {
        std::cin >> x;
    }

    auto c = std::vector<int>(n);
    for (auto &x: c)
    {
        std::cin >> x;
    }

    int m;
    std::cin >> m;

    int ans = 0;
    for (int idx = 0, i = 0, j = 0, k = 0, x, y, z; idx < m; ++idx)
    {
        std::cin >> x >> y >> z;

        i = (i + x) % n, j = (j + y) % n, k = (k + z) % n;

        auto t = std::array{a[i], b[j], c[k]};
        if (t[0] == t[1] && t[0] == t[2])
        {
            ans += 200;
        }
        else if (t[0] == t[1] || t[0] == t[2] || t[1] == t[2])
        {
            ans += 100;
        }
        else if (t[0] == t[1] - 1 && t[1] == t[2] - 1)
        {
            ans += 200;
        }
        else
        {
            ranges::sort(t);
            if (t[0] == t[1] - 1 && t[1] == t[2] - 1)
            {
                ans += 100;
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
