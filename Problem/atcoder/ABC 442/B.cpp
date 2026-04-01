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
    int q;
    std::cin >> q;

    int val = 0;
    bool status = false;
    while (q--)
    {
        int op;
        std::cin >> op;

        if (op == 1)
        {
            ++val;
        }
        else if (op == 2)
        {
            val = std::max(val - 1, 0);
        }
        else
        {
            status = !status;
        }

        std::cout << (status && val >= 3? "Yes\n": "No\n");
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
