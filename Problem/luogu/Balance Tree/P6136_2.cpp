#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = int64_t;

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

template<typename T1, typename T2 = __gnu_pbds::null_type, typename F1 = std::less<T1>>
using rb_tree = __gnu_pbds::tree<T1, T2, F1, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

void solve()
{
    int n, m;
    std::cin >> n >> m;

    rb_tree<std::array<int, 2>> tree;
    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;

        tree.insert({x, i});
    }

    int ans = 0;
    for (int i = 0, last = 0, op, x; i < m; ++i)
    {
        std::cin >> op >> x;

        x ^= last;
        if (op == 1)
        {
            tree.insert({x, n + i});
        }
        else if (op == 2)
        {
            tree.erase(tree.lower_bound({x, -1}));
        }
        else if (op == 3)
        {
            last = tree.order_of_key({x, -1}) + 1;
            ans ^= last;
        }
        else if (op == 4)
        {
            last = (*tree.find_by_order(x - 1))[0];
            ans ^= last;
        }
        else if (op == 5)
        {
            auto iter = tree.lower_bound({x, -1});
            --iter;

            last = (*iter)[0];
            ans ^= last;
        }
        else
        {
            last = (*tree.lower_bound({x, n + m}))[0];
            ans ^= last;
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
