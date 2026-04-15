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
    int n;
    std::cin >> n;

    int sum = lim<int>::min(), cnt = 0;
    for (int i = 0, num = 0, x; i < n; ++i)
    {
        std::cin >> x;

        if (x == 1)
        {
            ++cnt;
            x = -x;
        }
        else
        {
            x = 1;
        }

        num = std::max(x, num + x);
        sum = std::max(sum, num);
    }

    std::cout << sum + cnt << "\n";
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
