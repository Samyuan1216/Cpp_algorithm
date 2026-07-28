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

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    if (n & 1)
    {
        std::cout << "NO\n";
        return;
    }

    int min = 2e9, max = 0;
    for (int i = 0; i < n; ++i)
    {
        if (i & 1)
        {
            max = std::max(max, arr[i]);
        }
        else
        {
            min = std::min(min, arr[i]);
        }
    }

    std::cout << (max + 1 < min? "YES\n": "NO\n");
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
