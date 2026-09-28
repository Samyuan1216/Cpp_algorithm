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

    std::vector<int> a1, a2, a3;
    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;

        if (x < 0)
        {
            a1.push_back(x);
        }
        else if (x > 0)
        {
            a2.push_back(x);
        }
        else
        {
            a3.push_back(x);
        }
    }

    if (std::ssize(a1) % 2 == 0)
    {
        a3.push_back(a1.back());
        a1.pop_back();
    }

    if (a2.empty())
    {
        a2.push_back(a1.back());
        a1.pop_back();

        a2.push_back(a1.back());
        a1.pop_back();
    }

    std::cout << std::ssize(a1);
    for (auto &x: a1)
    {
        std::cout << " " << x;
    }
    std::cout << "\n";

    std::cout << std::ssize(a2);
    for (auto &x: a2)
    {
        std::cout << " " << x;
    }
    std::cout << "\n";

    std::cout << std::ssize(a3);
    for (auto &x: a3)
    {
        std::cout << " " << x;
    }
    std::cout << "\n";

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
