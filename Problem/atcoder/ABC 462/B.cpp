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

    std::vector<std::vector<int>> a(n);
    for (int i = 0, k, x; i < n; ++i)
    {
        std::cin >> k;
        while (k--)
        {
            std::cin >> x;

            a[x - 1].push_back(i);
        }
    }

    for (auto &line: a)
    {
        std::cout << std::ssize(line);
        for (auto &x: line)
        {
            std::cout << " " << x + 1;
        }
        std::cout << "\n";
    }
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
