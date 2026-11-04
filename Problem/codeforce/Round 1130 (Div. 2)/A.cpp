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
    int n, k;
    std::cin >> n >> k;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    std::vector<int> f(n + 1);
    f[n] = n;

    for (int i = n - 1; i >= 0; --i)
    {
        f[i] = std::min(arr[i], f[i + 1]);
    }

    if (f[n - k + 1] == n - k + 1)
    {
        std::cout << -1 << "\n";
        return;
    }

    int r, rmin = 1e9;
    for (int i = n - k + 1; i < n; ++i)
    {
        if (rmin > arr[i])
        {
            rmin = arr[i];
            r = i;
        }
    }

    int l, lmax = -1e9;
    for (int i = 0; i < n - k + 1; ++i)
    {
        if (lmax < arr[i])
        {
            lmax = arr[i];
            l = i;
        }
    }

    std::cout << l + 1 << " " << r + 1 << "\n";
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