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
    int k;
    std::cin >> k;

    std::vector<int> arr(k);
    for (auto &x: arr)
    {
        std::cin >> x;
    }


    ranges::sort(arr, std::greater());

    if ((k >= 1 && arr[0] >= 3) || (k >= 2 && arr[0] >= 2 && arr[1] >= 2))
    {
        std::cout << "YES\n";
    }
    else
    {
        std::cout << "NO\n";
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
