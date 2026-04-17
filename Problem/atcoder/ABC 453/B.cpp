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
    int t, x;
    std::cin >> t >> x;

    std::vector<std::array<int, 2>> arr;
    for (int i = 0, last = 0, num = 0; i <= t; ++i)
    {
        std::cin >> num;

        if (i == 0 || std::abs(num - last) >= x)
        {
            arr.push_back({i, num});
            last = num;
        }
    }

    ranges::sort(arr);

    for (auto &[idx, num]: arr)
    {
        std::cout << idx << " " << num << "\n";
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
