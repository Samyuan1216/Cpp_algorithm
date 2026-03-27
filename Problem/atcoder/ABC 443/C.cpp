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
    int n, t;
    std::cin >> n >> t;

    pq<std::pair<int, int>, std::greater<>> heap;
    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;

        heap.push({x, 0});
    }

    bool status = true;
    int ans = false, last = 0;
    while (!heap.empty())
    {
        auto [num, op] = heap.top();
        heap.pop();

        if (op == 0 && status)
        {
            ans += num - last;
            status = false;

            heap.push({num + 100, 1});
        }
        else if (op == 1)
        {
            last = num;
            status = true;
        }
    }

    if (status && last <= t)
    {
        ans += t - last;
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
