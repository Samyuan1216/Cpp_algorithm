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

    int sum = 0;
    bool s1 = false, s0 = false;

    for (int i = 0; i < n; ++i)
    {
        if (a[i] != b[i])
        {
            sum += a[i];
        }
        else
        {
            if (a[i] == 1)
            {
                s1 = true;
            }
            else
            {
                s0 = true;
            }
        }
    }

    if (a == b)
    {
        std::cout << 0 << "\n";
    }
    else if (sum & 1)
    {
        std::cout << 1 << "\n";
    }
    else if (sum > 1 || (s1 && s0))
    {
        std::cout << 2 << "\n";
    }
    else
    {
        std::cout << -1 << "\n";
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
