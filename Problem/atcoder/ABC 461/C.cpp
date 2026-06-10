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
    i64 n, k, m;
    std::cin >> n >> k >> m;

    std::vector<std::array<i64, 2>> arr(n);
    for (auto &[c, v]: arr)
    {
        std::cin >> c >> v;
    }

    ranges::sort(arr, std::greater());

    std::priority_queue<i64> heap;
    heap.push(arr[0][1]);

    for (int i = 1; i < n; ++i)
    {
        if (arr[i][0] != arr[i - 1][0])
        {
            heap.push(arr[i][1]);
        }
    }

    i64 ans = 0;
    k -= m;

    while (m--)
    {
        ans += heap.top();
        heap.pop();
    }

    for (int i = 1; i < n; ++i)
    {
        if (arr[i][0] == arr[i - 1][0])
        {
            heap.push(arr[i][1]);
        }
    }

    while (k--)
    {
        ans += heap.top();
        heap.pop();
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
