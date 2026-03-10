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
    int n;
    std::cin >> n;

    rb_tree<std::array<int, 2>> tree;
    for (int i = 0, op, x; i < n; ++i)
    {
        std::cin >> op >> x;

        if (op == 1)
        {
            tree.insert({x, i});
        }
        else if (op == 2)
        {
            auto iter = tree.lower_bound({x, -1});
            if (iter != tree.end() && (*iter)[0] == x)
            {
                tree.erase(iter);
            }
        }
        else if (op == 3)
        {
            std::cout << tree.order_of_key({x, -1}) + 1 << "\n";
        }
        else if (op == 4)
        {
            std::cout << (*tree.find_by_order(x - 1))[0] << "\n";
        }
        else if (op == 5)
        {
            auto iter = tree.lower_bound({x, -1});
            --iter;

            std::cout << (*iter)[0] << "\n";
        }
        else
        {
            std::cout << (*tree.upper_bound({x, n}))[0] << "\n";
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
