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
    int n, m;
    std::cin >> n >> m;

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    if (m == 1)
    {
        std::cout << *ranges::max_element(arr) << "\n";
        return;
    }

    std::priority_queue<i64> heap;
    i64 pre = 0;

    for (int i = 0; i < m - 1; ++i)
    {
        heap.push(arr[i]);
        pre += arr[i];
    }

    i64 ans = -1e18;
    for (int i = m - 1; i < n; ++i)
    {
        ans = std::max(ans, m * arr[i] - pre);
        if (arr[i] < heap.top())
        {
            pre -= heap.top();
            heap.pop();

            pre += arr[i];
            heap.push(arr[i]);
        }
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
