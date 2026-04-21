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
    i64 n, k, p, q;
    std::cin >> n >> k >> p >> q;

    std::vector<i64> arr(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];
    }

    if (n == 1)
    {
        std::cout << std::min(arr[1] % p % q, arr[1] % q % p) << "\n";
        return;
    }

    std::vector<i64> pre1(n + 1), pre2(n + 1), pre3(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        pre1[i] = pre1[i - 1] + arr[i] % p % q;
        pre2[i] = pre2[i - 1] + arr[i] % q % p;
        pre3[i] = pre3[i - 1] + std::min(arr[i] % p % q, arr[i] % q % p);
    }

    std::vector<i64> suf(n + 1);
    for (int i = n - 1; i >= 0; --i)
    {
        suf[i] = suf[i + 1] + std::min(arr[i + 1] % p % q, arr[i + 1] % q % p);
    }

    i64 ans = lim<i64>::max();
    for (int i = 1; i <= n - k + 1; ++i)
    {
        ans = std::min(ans, pre3[i - 1] + std::min(pre1[i + k - 1] - pre1[i - 1], pre2[i + k - 1] - pre2[i - 1]) + suf[i + k - 1]);
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
