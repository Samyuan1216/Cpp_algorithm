#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

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

    if (a == b)
    {
        std::cout << "Yes\n";
        return;
    }

    {
        auto sa = a, sb = b;
        ranges::sort(sa);
        ranges::sort(sb);

        if (sa != sb)
        {
            std::cout << "No\n";
            return;
        }
    }

    int l = -1, r = -1;
    for (int i = 0; i < n; ++i)
    {
        if (a[i] != b[i])
        {
            if (l == -1)
            {
                l = i;
            }

            r = i;
        }
    }

    auto check = [&](auto &a, auto &b) -> bool
    {
        for (int i = l; i < r; ++i)
        {
            if (a[i] != b[i + 1])
            {
                return false;
            }
        }

        return true;
    };

    std::cout << (check(a, b) || check(b, a)? "Yes\n": "No\n");
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    // std::cin >> t;
    while (t--)
    {
        solve();
    }
}