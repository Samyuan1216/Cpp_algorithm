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

    std::vector<int> p(n);
    for (auto &x: p)
    {
        std::cin >> x;
    }

    int ans = 0;
    std::vector<int> np;

    for (int i = 0, max = 0; i < n; ++i)
    {
        if (max < p[i])
        {
            ++ans;
            max = p[i];
        }
        else
        {
            np.push_back(p[i]);
        }
    }

    ans += [&](std::vector<int> &arr) -> int
    {
        std::vector<int> dp;

        int n = std::ssize(arr);
        for (int i = 0; i < n; ++i)
        {
            if (dp.empty() || arr[i] > arr[dp.back()])
            {
                dp.push_back(i);
            }
            else
            {
                auto iter = ranges::lower_bound(dp, arr[i], {}, [&](int idx) { return arr[idx]; });
                *iter = i;
            }
        }

        return std::ssize(dp);
    } (np);

    std::cout << ans << "\n";
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
