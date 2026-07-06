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

    std::vector<i64> a(n);
    for (auto &x: a)
    {
        std::cin >> x;
    }

    std::vector<i64> b(n);
    for (auto &x: b)
    {
        std::cin >> x;
    }

    if (a[n - 1] <= b[n - 1])
    {
        a[n - 1] = b[n - 1];
    }

    for (int i = n - 2; i >= 0; --i)
    {
        if (a[i + 1] > b[i + 1])
        {
            a[i] += a[i + 1] - b[i + 1];
            a[i + 1] = b[i + 1];
        }

        if (a[i] <= b[i])
        {
            a[i] = b[i];
        }
    }

    std::cout << (a == b? "YES\n": "NO\n");
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
