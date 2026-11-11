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
    int n, k;
    std::cin >> n >> k;

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

    int cnta = 0;
    for (auto &x: a)
    {
        if (x & 1)
        {
            ++cnta;
        }
    }

    int cntb = 0;
    for (auto &x: b)
    {
        if (x & 1)
        {
            ++cntb;
        }
    }

    if (((k & 1) && cnta <= cntb) || (k % 2 == 0 && cnta >= cntb))
    {
        std::cout << "YES\n";
    }
    else
    {
        std::cout << "NO\n";
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