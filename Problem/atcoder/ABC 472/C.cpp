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
    i64 n, m, k;
    std::cin >> n >> m >> k;

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    std::vector<bool> eat(n);
    for (i64 l = 0, r = 0, pre = 0; r < n; ++r)
    {
        if (pre + arr[r] <= k)
        {
            pre += arr[r];
            eat[r] = true;

            std::cout << "Yes\n";
        }
        else
        {
            std::cout << "No\n";
        }

        if (l == r - m + 1)
        {
            if (eat[l])
            {
                pre -= arr[l];
            }

            ++l;
        }
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
