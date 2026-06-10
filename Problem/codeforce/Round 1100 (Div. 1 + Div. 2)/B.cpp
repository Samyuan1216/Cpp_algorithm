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

    i64 sum = 0;
    for (int i = 0; i < n; ++i)
    {
        if (a[i] > b[i])
        {
            std::swap(a[i], b[i]);
        }

        sum += b[i];
    }

    std::cout << *ranges::max_element(a) + sum << "\n";
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
