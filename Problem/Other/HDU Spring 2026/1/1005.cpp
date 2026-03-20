#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = int64_t;

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

    auto arr = std::vector(n, std::array<i64, 2>());
    for (auto &[s, d]: arr)
    {
        std::cin >> s >> d;
    }

    ranges::sort(arr);

    i64 ans = 0;
    for (int i = 0; i < n; ++i)
    {
        if (ans < arr[i][0])
        {
            ans = arr[i][0];
        }

        ans += arr[i][1];
    }

    std::cout << ans << "\n";
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
