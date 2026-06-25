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

    std::vector<std::array<i64, 4>> arr1(n);
    for (i64 i = 0, x; auto &a: arr1)
    {
        std::cin >> x;

        a[0] = a[1] = a[2] = x - i;
        a[3] = 1;
        ++i;
    }

    std::vector<i64> prev(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        prev[i] = prev[i - 1] + arr1[i - 1][0];
    }

    auto floor_div = [](i64 a, i64 b) -> i64
    {
        return (a >= 0? a / b: (a - b + 1) / b);
    };

    std::stack<std::array<i64, 4>> sta;
    for (auto &a: arr1)
    {
        while (!sta.empty() && sta.top()[1] > a[0])
        {
            auto t = sta.top();
            sta.pop();

            i64 s = a[2] + t[2], l = a[3] + t[3];
            a[0] = floor_div(s, l), a[1] = floor_div(s + l - 1, l);
            a[2] = s, a[3] = l;
        }

        sta.push(a);
    }

    std::vector<i64> arr2(n);
    int idx = n - 1;

    while (!sta.empty())
    {
        auto t = sta.top();
        sta.pop();

        i64 s = t[2], l = t[3];
        for (int i = 0; i < l; ++i)
        {
            arr2[idx - l + 1 + i] = floor_div(s + i, l);
        }

        idx -= l;
    }

    std::vector<i64> cur(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        cur[i] = cur[i - 1] + arr2[i - 1];
    }

    i64 ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        ans += prev[i] - cur[i];
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
