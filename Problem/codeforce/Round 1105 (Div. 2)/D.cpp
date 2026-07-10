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
    int n, d;
    std::cin >> n >> d;

    std::vector<i64> arr(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];
    }

    std::vector<i64> sum(3 * n + 1);
    for (int i = 1; i <= 3 * n; ++i)
    {
        sum[i] = sum[i - 1] + arr[(i - 1) % n + 1];
    }

    i64 ans = 0;
    for (int i = 1, idx = n + 1; i <= n; ++i, ++idx)
    {
        i64 delta = (2ll * d + 1) * arr[i] - (sum[idx + d] - sum[idx - d - 1]);
        if (delta > 0)
        {
            ans += delta;
        }
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
