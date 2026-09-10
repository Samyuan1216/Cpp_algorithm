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
    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<int> b(m);
    for (auto &x: b)
    {
        std::cin >> x;
    }

    ranges::sort(b);
    auto [l, r] = ranges::unique(b);
    b.erase(l, r);

    while (q--)
    {
        int a;
        std::cin >> a;

        auto iter = ranges::lower_bound(b, a);
        if (iter == b.end())
        {
            std::cout << n - *std::prev(iter) << "\n";
        }
        else if (iter == b.begin())
        {
            std::cout << *iter - 1 << "\n";
        }
        else
        {
            std::cout << (*iter - *std::prev(iter)) / 2 << "\n";
        }
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
