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

    ranges::sort(arr);

    int mex = 0;
    for (int i = 0, rem = 0; i < n; ++i)
    {
        while (i + 1 < n && mex == arr[i + 1])
        {
            ++i;
            ++rem;
        }

        if (mex < arr[i] || rem + 1 < k)
        {
            break;
        }

        rem -= k - 1;
        ++mex;
    }

    std::cout << mex << "\n";
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