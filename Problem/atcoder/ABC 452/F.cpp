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
    i64 n, k;
    std::cin >> n >> k;

    auto arr = std::vector<int>(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    namespace pbds = __gnu_pbds;
    auto tr1 = pbds::tree<int, pbds::null_type, std::greater<>, pbds::rb_tree_tag, pbds::tree_order_statistics_node_update>();
    i64 inv1 = 0;
    int l1 = 0;

    auto tr2 = pbds::tree<int, pbds::null_type, std::greater<>, pbds::rb_tree_tag, pbds::tree_order_statistics_node_update>();
    i64 inv2 = 0;
    int l2 = 0;

    i64 ans = 0;
    for (int r = 0; r < n; ++r)
    {
        inv1 += tr1.order_of_key(arr[r]);
        tr1.insert(arr[r]);

        while (l1 <= r && inv1 > k)
        {
            tr1.erase(arr[l1]);
            inv1 -= std::ssize(tr1) - tr1.order_of_key(arr[l1]);

            ++l1;
        }

        inv2 += tr2.order_of_key(arr[r]);
        tr2.insert(arr[r]);

        while (l2 <= r && inv2 > k - 1)
        {
            tr2.erase(arr[l2]);
            inv2 -= std::ssize(tr2) - tr2.order_of_key(arr[l2]);

            ++l2;
        }

        ans += l2 - l1;
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
