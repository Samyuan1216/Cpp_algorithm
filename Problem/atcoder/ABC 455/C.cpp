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
    i64 n, k;
    std::cin >> n >> k;

    std::vector<i64> arr(n);
    i64 ans = 0;

    for (auto &x: arr)
    {
        std::cin >> x;

        ans += x;
    }

    ranges::sort(arr);

    std::vector<i64> sum;
    for (int i = 0; i < n; ++i)
    {
        if (i == 0 || arr[i] != arr[i - 1])
        {
            sum.push_back(arr[i]);
        }
        else
        {
            sum.back() += arr[i];
        }
    }

    ranges::sort(sum, std::greater<>());

    for (int i = 0; i < std::min(k, i64(std::ssize(sum))); ++i)
    {
        ans -= sum[i];
    }

    std::cout << ans << "\n";
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
