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

    std::priority_queue<i64, std::vector<i64>, std::greater<>> heap;
    i64 ans = 0, day = 0;
    for (int i = 0; i < n; ++i)
    {
        day = arr[i][0];
        if (heap.empty() || std::ssize(heap) < day || heap.top() < arr[i][1])
        {
            ans += arr[i][1];
            if (std::ssize(heap) >= day)
            {
                ans -= heap.top();
                heap.pop();
            }

            heap.push(arr[i][1]);
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
