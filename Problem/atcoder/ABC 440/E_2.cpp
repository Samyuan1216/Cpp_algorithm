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
    int n, k, x;
    std::cin >> n >> k >> x;

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    ranges::sort(arr, std::greater());

    std::priority_queue<std::array<i64, 4>> heap;
    heap.push({k * arr[0], 0, k, 0});

    while (x--)
    {
        auto cur = heap.top();
        heap.pop();

        std::cout << cur[0] << "\n";

        if (cur[1] + 1 < n)
        {
            heap.push({cur[0] - arr[cur[1]] + arr[cur[1] + 1], cur[1] + 1, 1, cur[2] - 1});
        }

        if (cur[1] > 0 && cur[3] > 0)
        {
            heap.push({cur[0] - arr[cur[1] - 1] + arr[cur[1]], cur[1], cur[2] + 1, cur[3] - 1});
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
