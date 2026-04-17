#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

template<typename T>
using lim = std::numeric_limits<T>;

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

    std::vector<std::array<i64, 2>> arr(n);
    for (auto &[d, p]: arr)
    {
        std::cin >> d >> p;
    }

    ranges::sort(arr);

    std::priority_queue<i64> heap;
    i64 ans = 0;
    for (int l = n - 1, r = n - 1; r >= 0; r = l)
    {
        while (l >= 0 && arr[l][0] == arr[r][0])
        {
            heap.push(arr[l][1]);
            --l;
        }

        int day = arr[r][0] - arr[l][0];
        while (!heap.empty() && day > 0)
        {
            ans += heap.top();
            heap.pop();

            --day;
        }
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
