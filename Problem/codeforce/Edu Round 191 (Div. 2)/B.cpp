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

    bool status = false;
    if (n & 1)
    {
        status = true;

        std::vector<int> arr{1, 1, 2, 1, 2, 3, 1, 3, 2, 2, 3, 3};
        for (int i = 0; i < 12; ++i)
        {
            std::cout << arr[i] << " ";
        }

        n -= 3;
    }

    std::vector<int> arr{1, 2, 1, 2, 2, 1, 1, 2};
    for (int base = (status? 3: 0); base - (status? 3: 0) < n; base += 2)
    {
        for (int i = 0; i < 8; ++i)
        {
            std::cout << base + arr[i] << " ";
        }
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
