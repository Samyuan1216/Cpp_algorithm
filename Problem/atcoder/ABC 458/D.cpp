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
    int x, q;
    std::cin >> x >> q;

    std::multiset<int> arr;
    auto iter = arr.insert(x);

    while (q--)
    {
        int a, b;
        std::cin >> a >> b;

        arr.insert(a);
        arr.insert(b);

        if (a >= *iter && b >= *iter)
        {
            ++iter;
        }
        else if (a < *iter && b < *iter)
        {
            --iter;
        }

        std::cout << *iter << "\n";
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
