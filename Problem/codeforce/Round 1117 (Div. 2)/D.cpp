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
    i64 s, q;
    std::cin >> s >> q;

    std::vector<i64> arr{1, s};
    for (i64 p = 2; p * p <= s; ++p)
    {
        if (s % p == 0)
        {
            arr.push_back(p);
            if (p * p != s)
            {
                arr.push_back(s / p);
            }
        }
    }

    ranges::sort(arr);

    std::vector<i64> sum(std::ssize(arr));
    sum[0] = s;

    for (int i = 1; i < std::ssize(arr); ++i)
    {
        sum[i] = sum[i - 1] + (s / arr[i]) * (arr[i] - arr[i - 1]);
    }

    auto compute = [&](i64 w) -> i64
    {
        int k = std::distance(arr.begin(), ranges::upper_bound(arr, w)) - 1;
        i64 res = sum[k];

        if (k + 1 < std::ssize(arr))
        {
            res += (w - arr[k]) * (s / arr[k + 1]);
        }

        return res;
    };

    while (q--)
    {
        i64 x, y;
        std::cin >> x >> y;

        int k = std::distance(arr.begin(), ranges::upper_bound(arr, s / y)) - 1;
        i64 w = arr[k], ans;

        if (x <= w)
        {
            ans = x * y;
        }
        else
        {
            ans = w * y + compute(x) - compute(w);
        }

        std::cout << ans << "\n";
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
