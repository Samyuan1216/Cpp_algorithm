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
    int n;
    std::cin >> n;

    std::priority_queue<std::array<int, 2>> heap;
    for (int i = 0, h, l; i < n; ++i)
    {
        std::cin >> h >> l;

        heap.push({l * 2, h});
    }

    int q;
    std::cin >> q;

    std::vector<std::array<int, 2>> times(q);
    for (int i = 0; auto &[x, id]: times)
    {
        std::cin >> x;

        x = 2 * x + 1;
        id = i++;
    }

    ranges::sort(times, std::greater());

    std::vector<int> ans(q);
    int max = 0;

    for (int i = 0; i < q; ++i)
    {
        while (!heap.empty() && heap.top()[0] > times[i][0])
        {
            max = std::max(max, heap.top()[1]);
            heap.pop();
        }

        ans[times[i][1]] = max;
    }

    for (auto &x: ans)
    {
        std::cout << x << "\n";
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
