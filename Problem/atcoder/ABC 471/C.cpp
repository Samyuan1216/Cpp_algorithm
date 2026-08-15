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

    std::vector<int> arr(n + 1);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> arr[i];
    }

    ranges::sort(arr);

    std::vector<int> prev(n + 1), next(n + 1);
    for (int i = 0; i < n + 1; ++i)
    {
        prev[i] = i - 1;
        next[i] = i + 1;
    }

    int cur = std::distance(arr.begin(), ranges::lower_bound(arr, 0));
    i64 ans = 0;

    for (int i = 0; i < n; ++i)
    {
        int choose;
        if (prev[cur] < 0)
        {
            choose = next[cur];
        }
        else if (next[cur] >= n + 1)
        {
            choose = prev[cur];
        }
        else
        {
            if (arr[cur] - arr[prev[cur]] <= arr[next[cur]] - arr[cur])
            {
                choose = prev[cur];
            }
            else
            {
                choose = next[cur];
            }
        }

        ans += std::abs(arr[cur] - arr[choose]);
        if (prev[cur] >= 0)
        {
            next[prev[cur]] = next[cur];
        }

        if (next[cur] < n + 1)
        {
            prev[next[cur]] = prev[cur];
        }

        cur = choose;
    }

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
