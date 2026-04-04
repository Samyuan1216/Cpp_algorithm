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
    int n, m;
    std::cin >> n >> m;

    using ph = __gnu_pbds::priority_queue<std::array<int, 2>, std::greater<std::array<int, 2>>, __gnu_pbds::pairing_heap_tag>;
    auto arr = std::vector(n + 1, ph());
    for (int i = 1, x; i <= n; ++i)
    {
        std::cin >> x;

        arr[i].push({x, i});
    }

    auto father = std::vector<int>(n + 1);
    ranges::iota(father, 0);

    auto find = [&](this auto &&self, int i) -> int
    {
        father[i] = (father[i] == i? i: self(father[i]));
        return father[i];
    };

    auto del = std::vector<bool>(n + 1);
    while (m--)
    {
        int op;
        std::cin >> op;

        if (op == 1)
        {
            int x, y;
            std::cin >> x >> y;

            if (del[x] || del[y])
            {
                continue;
            }

            int fx = find(x), fy = find(y);
            if (fx != fy)
            {
                arr[fx].join(arr[fy]);
                father[fy] = fx;
            }
        }
        else
        {
            int x;
            std::cin >> x;

            if (del[x])
            {
                std::cout << -1 << "\n";
            }
            else
            {
                int fx = find(x);
                auto [val, id] = arr[fx].top();
                arr[fx].pop();

                del[id] = true;
                std::cout << val << "\n";
            }
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
