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

    auto tmp = arr;
    arr.insert(arr.end(), tmp.begin(), tmp.end());

    i64 sum = 0, ans = 0;
    for (int i = 0, len = 0; i <= n; ++i)
    {
        sum += arr[i];
        if (sum < 0)
        {
            sum = 0, len = 0;
            ans = i + 1;
            continue;
        }

        ++len;
        if (len == n)
        {
            break;
        }
    }

    std::cout << ans + 1 << "\n";
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
