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

    std::vector<i64> ans(n);
    ans[0] = arr[0];

    for (i64 i = 1, prev = 0; i < n; ++i)
    {
        arr[i] += prev;
        prev = 0;

        if (arr[i] >= ans[i - 1])
        {
            prev += arr[i] - ans[i - 1];
            ans[i] = ans[i - 1];
            continue;
        }

        i64 k = (ans[i - 1] - arr[i] + i) / (i + 1);
        arr[i] += i * k;
        ans[i] = ans[i - 1] - k;
        prev = arr[i] - ans[i];
    }

    for (int i = 0; i < n; ++i)
    {
        std::cout << ans[i] << " \n"[i == n - 1];
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
