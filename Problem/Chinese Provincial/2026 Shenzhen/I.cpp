#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

template<typename T>
using lim = std::numeric_limits<T>;

void solve()
{
    int n;
    std::cin >> n;

    if ((n >= 9 && n <= 10) || (n >= 12 && n <= 21) || (n >= 23 && n <= 32) || (n >= 34))
    {
        std::cout << "No\n";
        return;
    }

    std::cout << "Yes\n";
    if (n == 0)
    {
        std::cout << "1 1 1 1 1 1 1 1 1 1 1 1\n";
    }
    else if (n == 1)
    {
        std::cout << "0 0 0 0 0 0 0 0 0 0 0 0\n";
    }
    else if (n == 2)
    {
        std::cout << "1 0 0 0 0 0 0 0 0 0 0 0\n";
    }
    else if (n == 3)
    {
        std::cout << "1 2 0 0 0 0 0 0 0 0 0 0\n";
    }
    else if (n == 4)
    {
        std::cout << "1 2 3 0 0 0 0 0 0 0 0 0\n";
    }
    else if (n == 5)
    {
        std::cout << "1 2 3 4 0 0 0 0 0 0 0 0\n";
    }
    else if (n == 6)
    {
        std::cout << "1 2 3 4 5 0 0 0 0 0 0 0\n";
    }
    else if (n == 7)
    {
        std::cout << "1 2 3 4 5 0 6 0 0 0 0 0\n";
    }
    else if (n == 8)
    {
        std::cout << "1 2 3 4 5 0 6 7 0 0 0 0\n";
    }
    else if (n == 11)
    {
        std::cout << "1 2 3 4 5 0 6 7 8 0 0 0\n";
    }
    else if (n == 22)
    {
        std::cout << "1 2 3 4 5 0 6 7 8 1 0 0\n";
    }
    else if (n == 33)
    {
        std::cout << "1 2 3 4 5 0 6 7 8 1 2 0\n";
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
