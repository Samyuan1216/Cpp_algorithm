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
    int q, v;
    std::cin >> q >> v;

    std::priority_queue<int, std::vector<int>, std::greater<>> heap;
    while (q--)
    {
        int op;
        std::cin >> op;

        if (op == 1)
        {
            int t, w;
            std::cin >> t >> w;

            heap.push(t + (v - w));
        }
        else
        {
            int t;
            std::cin >> t;

            if (heap.empty())
            {
                std::cout << -1 << "\n";
                continue;
            }

            int ans = heap.top();
            heap.pop();

            std::cout << (ans <= t? v: v + (t - ans)) << "\n";
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
