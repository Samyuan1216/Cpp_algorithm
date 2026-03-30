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
    int n, m, k;
    std::cin >> n >> m >> k;

    auto c = std::vector<i64>(n - 1);
    for (auto &x: c)
    {
        std::cin >> x;
    }

    for (int i = 1; i < n - 1; ++i)
    {
        c[i] += c[i - 1];
    }

    auto a = std::vector<int>(n);
    for (auto &x: a)
    {
        std::cin >> x;
    }

    auto heap = pq<i64, std::greater<>>();
    i64 ans = 0, sum = 0;
    for (int i = 0; i < n; ++i)
    {
        i64 cost = (i == 0? 0: c[i - 1]);

        heap.push(a[i]);
        sum += a[i];

        while (std::ssize(heap) > k)
        {
            sum -= heap.top();
            heap.pop();
        }

        ans = std::max(ans, std::min(sum, m - cost));
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
