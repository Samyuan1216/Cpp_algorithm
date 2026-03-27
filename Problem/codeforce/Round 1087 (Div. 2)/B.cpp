#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

template<typename T>
using lim = std::numeric_limits<T>;

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

    auto arr = std::vector<int>(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    auto up = std::vector<int>(n), down = std::vector<int>(n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (arr[j] > arr[i])
            {
                ++up[i];
            }
            else if (arr[j] < arr[i])
            {
                ++down[i];
            }
        }
    }

    for (int i = 0; i < n; ++i)
    {
        std::cout << std::max(up[i], down[i]) << " \n"[i == n - 1];
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
