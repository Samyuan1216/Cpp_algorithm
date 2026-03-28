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
    int q;
    std::cin >> q;

    auto heap = pq<int, std::greater<>>();
    while (q--)
    {
        int op, h;
        std::cin >> op >> h;

        if (op == 1)
        {
            heap.push(h);
        }
        else
        {
            while (!heap.empty() && heap.top() <= h)
            {
                heap.pop();
            }
        }

        std::cout << heap.size() << "\n";
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
