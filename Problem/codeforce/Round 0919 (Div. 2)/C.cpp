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

    std::vector<int> ks;
    for (int p = 1; p * p <= n; ++p)
    {
        if (n % p == 0)
        {
            ks.push_back(p);
            if (p * p != n)
            {
                ks.push_back(n / p);
            }
        }
    }

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    int ans = 0;
    for (auto &k: ks)
    {
        if (k == n)
        {
            ++ans;
            continue;
        }

        int idx = k, g = 0;
        while (idx < n)
        {
            for (int i = 0; i < k; ++i, ++idx)
            {
                g = std::gcd(g, std::abs(arr[idx] - arr[i]));
            }
        }

        if (g != 1)
        {
            ++ans;
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
