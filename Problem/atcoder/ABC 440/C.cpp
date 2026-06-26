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
    int n, w;
    std::cin >> n >> w;

    std::vector<int> arr(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];
    }

    std::vector<std::array<int, 2>> block;
    for (int base = -2; base * w <= n; base += 2)
    {
        block.push_back({base * w, base * w + w});
    }

    i64 cost = 0;
    for (auto &[l, r]: block)
    {
        for (int i = std::max(1, l); i < std::min(n + 1, r); ++i)
        {
            cost += arr[i];
        }
    }

    i64 ans = cost;
    for (int i = 1; i < 2 * w; ++i)
    {
        for (auto &[l, r]: block)
        {
            if (l >= 1 && l <= n)
            {
                cost -= arr[l];
            }
            ++l;

            if (r >= 1 && r <= n)
            {
                cost += arr[r];
            }
            ++r;
        }

        ans = std::min(ans, cost);
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
