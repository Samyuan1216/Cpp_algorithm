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
    int a, b, c;
    std::cin >> a >> b >> c;

    std::vector<int> x;
    for (int i = 0; i < a; ++i)
    {
        x.push_back(i);
    }

    std::vector<int> y;
    for (int i = 0; i < b; ++i)
    {
        y.push_back(i);
    }

    for (auto &i: x)
    {
        for (auto &j: y)
        {
            if ((i ^ j) == c)
            {
                std::cout << "No\n";
                return;
            }
        }
    }

    std::cout << "Yes\n";

    x.push_back(1024);
    for (int i = 0; i < c; ++i)
    {
        y.push_back(1024 + i);
    }

    std::cout << std::ssize(x);
    for (int i = 0; i < std::ssize(x); ++i)
    {
        std::cout << " " << x[i];
    }
    std::cout << "\n";

    std::cout << std::ssize(y);
    for (int i = 0; i < std::ssize(y); ++i)
    {
        std::cout << " " << y[i];
    }
    std::cout << "\n";
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