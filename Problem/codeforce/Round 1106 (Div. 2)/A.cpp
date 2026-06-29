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
    int n, c;
    std::cin >> n >> c;

    std::vector<int> a(n);
    for (auto &x: a)
    {
        std::cin >> x;
    }

    std::vector<int> b(n);
    for (auto &x: b)
    {
        std::cin >> x;
    }

    int ans1 = 0;
    for (int i = 0; i < n; ++i)
    {
        if (b[i] > a[i])
        {
            ans1 = -1;
            break;
        }

        ans1 += a[i] - b[i];
    }

    ranges::sort(a);
    ranges::sort(b);

    int ans2 = c;
    for (int i = 0; i < n; ++i)
    {
        if (b[i] > a[i])
        {
            ans2 = -1;
            break;
        }

        ans2 += a[i] - b[i];
    }

    if (ans1 == -1)
    {
        std::cout << ans2 << "\n";
    }
    else
    {
        std::cout << std::min(ans1, ans2) << "\n";
    }
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
