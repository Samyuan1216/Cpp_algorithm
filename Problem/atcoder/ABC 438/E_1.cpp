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
    int n, q;
    std::cin >> n >> q;

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
        --x;
    }

    constexpr int limit = 32;
    std::vector<std::array<i64, limit>> stjump(n), stsum(n);

    for (int i = 0; i < n; ++i)
    {
        stjump[i][0] = arr[i];
        stsum[i][0] = i + 1;
    }

    for (int p = 1; p < limit; ++p)
    {
        for (int i = 0; i < n; ++i)
        {
            stjump[i][p] = stjump[stjump[i][p - 1]][p - 1];
            stsum[i][p] = stsum[i][p - 1] + stsum[stjump[i][p - 1]][p - 1];
        }
    }

    while (q--)
    {
        i64 t, b;
        std::cin >> t >> b;
        --b;

        i64 ans = 0, cur = b;
        for (int p = limit - 1; p >= 0; --p)
        {
            if ((t >> p) & 1)
            {
                ans += stsum[cur][p];
                cur = stjump[cur][p];
            }
        }

        std::cout << ans << "\n";
    }
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
