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
    i64 n, m;
    std::cin >> n >> m;

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    ranges::sort(arr);

    i64 x = 0, y = 1, fin = m, rem = m;
    for (int i = 0; i < n; ++i)
    {
        i64 need = std::max(0ll, arr[i] - x);
        i64 time = (need + y - 1) / y;

        if (rem < time)
        {
            break;
        }

        x += time * y;

        i64 ifin = x - arr[i] + (rem - time) * (y + 1);
        if (ifin > fin)
        {
            fin = ifin;
            x -= arr[i];
            ++y;
        }

        rem -= time;
    }

    std::cout << fin << "\n";
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
