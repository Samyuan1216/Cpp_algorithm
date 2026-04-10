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
    int n, k;
    std::cin >> n >> k;

    auto arr = std::vector<int>(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    int p;
    std::cin >> p;

    int aim = (arr[p - 1] == 0? 1: 0);
    arr[p - 1] = 2;

    auto [l, r] = ranges::unique(arr);
    arr.erase(l, r);

    p = std::distance(arr.begin(), ranges::find(arr, 2));

    int lcnt = 0;
    for (int i = p - 1; i >= 0; --i)
    {
        if (arr[i] == aim)
        {
            ++lcnt;
        }
    }

    lcnt = 2 * lcnt;

    int rcnt = 0;
    for (int i = p + 1; i < std::ssize(arr); ++i)
    {
        if (arr[i] == aim)
        {
            ++rcnt;
        }
    }

    rcnt = 2 * rcnt;

    std::cout << std::max(lcnt, rcnt) << "\n";
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
