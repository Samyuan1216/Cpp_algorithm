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

void solve(int n)
{
    using pq = __gnu_pbds::priority_queue<int>;
    std::vector<pq> arr(n);
    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;

        arr[i].push(x);
    }

    std::vector<int> father(n);
    ranges::iota(father, 0);

    auto find = [&](this auto &&find, int i) -> int
    {
        father[i] = (father[i] == i? i: find(father[i]));
        return father[i];
    };

    auto fight = [&](int x, int y) -> int
    {
        x = find(x), y = find(y);
        if (x == y)
        {
            return -1;
        }

        int l = arr[x].top(), r = arr[y].top();
        arr[x].pop(), arr[y].pop();

        l /= 2, r /= 2;
        arr[x].push(l), arr[y].push(r);

        father[y] = x;
        arr[x].join(arr[y]);

        return arr[x].top();
    };

    int m;
    std::cin >> m;

    while (m--)
    {
        int x, y;
        std::cin >> x >> y;
        --x, --y;

        std::cout << fight(x, y) << "\n";
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    while (std::cin >> t)
    {
        solve(t);
    }
}
