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

    ranges::sort(arr);

    int max = 0, max_cnt = 0;
    for (int l = 0, r = 0; r < n; l = r)
    {
        while (r < n && arr[r] == arr[l])
        {
            ++r;
        }

        if (r - l >= max_cnt)
        {
            max = arr[l];
            max_cnt = r - l;
        }
    }

    int other = n - max_cnt, sum = 0;
    for (int i = 0, cnt = max_cnt; i < n; ++i)
    {
        if (arr[i] == max && cnt <= max_cnt - other - 2)
        {
            continue;
        }

        if (arr[i] == max)
        {
            --cnt;
        }

        sum += arr[i];
    }

    std::cout << sum << "\n";
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
