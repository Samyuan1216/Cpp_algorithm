#include <bits/stdc++.h>
#include <bits/extc++.h>
namespace ranges = std::ranges;
namespace views = std::views;

using i64 = int64_t;
using i128 = __int128;
using u64 = uint64_t;
using u128 = unsigned __int128;
using f64 = double;
using f128 = long double;

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

template<typename T = int, typename Cmp = std::less<T>, typename Tag = __gnu_pbds::pairing_heap_tag>
using pq = __gnu_pbds::priority_queue<T, Cmp, Tag>;

void solve()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<std::array<int, 2>> arr(n);
    for (auto &p: arr)
    {
        std::cin >> p[1] >> p[0];
    }

    ranges::sort(arr, std::greater());

    pq<int, std::greater<>> heap;
    std::vector<i64> pre(n + 1);

    i64 maxn = 0, cur = 0;
    for (int i = n, j = 0; i >= 0; --i)
    {
        while (j < n && arr[j][0] >= i)
        {
            cur += arr[j][1];
            heap.push(arr[j++][1]);
        }

        while (std::ssize(heap) > i + 1)
        {
            cur -= heap.top();
            heap.pop();
        }

        maxn = std::max(maxn, cur);
        pre[i] = (std::ssize(heap) <= i? cur: cur - heap.top());
    }

    for (int i = 1; i <= n; ++i)
    {
        pre[i] = std::max(pre[i], pre[i - 1]);
    }

    while (m--)
    {
        int x, y;
        std::cin >> x >> y;
        std::cout << std::max(maxn, pre[y] + x) << " \n"[m == 0];
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
