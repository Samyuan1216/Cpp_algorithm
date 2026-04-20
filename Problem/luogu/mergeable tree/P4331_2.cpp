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

    std::vector<i64> arr(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> arr[i];

        arr[i] -= i;
    }

    using pq = __gnu_pbds::priority_queue<i64>;
    std::vector<pq> heap(n);

    for (int i = 0; i < n; ++i)
    {
        heap[i].push(arr[i]);
    }

    std::vector<int> father(n), from(n), to(n);
    ranges::iota(father, 0);
    ranges::iota(from, 0);
    ranges::iota(to, 0);

    auto find = [&](this auto &&find, int i) -> int
    {
        father[i] = (father[i] == i? i: find(father[i]));
        return father[i];
    };

    std::stack<int> sta;
    for (int i = 0, pre, cur; i < n; ++i)
    {
        while (!sta.empty())
        {
            pre = find(sta.top()), cur = find(i);
            if (heap[pre].top() <= heap[cur].top())
            {
                break;
            }

            heap[cur].join(heap[pre]);
            father[pre] = cur;

            while (std::ssize(heap[cur]) > (i - from[pre] + 1 + 1) / 2)
            {
                heap[cur].pop();
            }

            from[cur] = from[pre];
            to[cur] = i;

            sta.pop();
        }

        sta.push(i);
    }

    i64 sum = 0;
    std::vector<i64> ans(n);

    while (!sta.empty())
    {
        int cur = find(sta.top());
        for (int i = from[cur]; i <= to[cur]; ++i)
        {
            ans[i] = heap[cur].top();
            sum += std::abs(ans[i] - arr[i]);
        }

        sta.pop();
    }

    std::cout << sum << "\n";
    for (int i = 0; i < n; ++i)
    {
        std::cout << ans[i] + i << " \n"[i == n - 1];
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
