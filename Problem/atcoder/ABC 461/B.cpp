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

    for (int i = 0; i < n; ++i)
    {
        if (b[a[i] - 1] != i + 1)
        {
            std::cout << "No\n";
            return;
        }
    }

    std::cout << "Yes\n";
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
