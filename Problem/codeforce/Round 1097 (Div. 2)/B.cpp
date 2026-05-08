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

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    ranges::sort(arr);
    ranges::unique(arr);

    auto iter = ranges::max_element(arr);
    ranges::rotate(arr.begin(), iter, iter + 1);


    i64 ans = 0, mex = 0, max = arr[0];
    for (int i = 0; i < n; ++i)
    {
        if (mex == arr[i])
        {
            ++mex;
        }

        if (mex == max)
        {
            ++mex;
        }

        ans += mex + max;
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
