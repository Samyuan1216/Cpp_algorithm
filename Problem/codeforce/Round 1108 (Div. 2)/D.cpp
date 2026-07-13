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

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    auto get_cost = [&](i64 x) -> i64
    {
        using u64 = unsigned long long;
        return std::popcount(u64(x)) + std::bit_width(u64(x)) - 1;
    };

    i64 ans = -1;
    for (int k = 0, base = 1; k <= 20; ++k, base <<= 1)
    {
        i64 cur = k;
        bool ok = true;

        for (int i = 0; i < n; ++i)
        {
            i64 min = -1;
            i64 x0 = arr[i] + (arr[i] % base == 0 ? 0 : base - arr[i] % base);

            for (i64 x = x0, total; x - x0 <= 40; x += base)
            {
                total = x - arr[i] + get_cost(x >> k);
                if (min == -1 || total < min)
                {
                    min = total;
                }
            }

            if (min == -1)
            {
                ok = false;
                break;
            }

            cur += min;
        }

        if(ok && (ans == -1 || cur < ans))
        {
            ans = cur;
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
