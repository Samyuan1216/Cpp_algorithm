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

template<typename T = int, typename Cmp = std::less<T>>
using pq = std::priority_queue<T, std::vector<T>, Cmp>;

void solve()
{
    int n;
    std::cin >> n;

    auto arr = std::vector<int>(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    auto dist = arr;
    auto heap = pq<std::pair<int, int>, std::greater<>>();
    for (int i = 0; i < n; ++i)
    {
        heap.push({dist[i], i});
    }

    while (!heap.empty())
    {
        auto [d, u] = heap.top();
        heap.pop();

        if (d > dist[u])
        {
            continue;
        }

        if (u > 0 && dist[u - 1] - 1 > d)
        {
            dist[u - 1] = d + 1;
            heap.push({dist[u - 1], u - 1});
        }

        if (u < n - 1 && dist[u + 1] - 1 > d)
        {
            dist[u + 1] = d + 1;
            heap.push({dist[u + 1], u + 1});
        }
    }

    i64 ans = 0;
    for (int i = 0; i < n; ++i)
    {
        ans += arr[i] - dist[i];
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
