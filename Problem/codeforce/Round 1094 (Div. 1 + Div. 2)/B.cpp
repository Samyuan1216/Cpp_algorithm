#include <bits/extc++.h>
namespace ranges = std::ranges;
namespace pbds = __gnu_pbds;

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

    std::vector<int> o, e;
    i64 sum = 0;

    for (int i = 1, x; i <= n; ++i)
    {
        std::cin >> x;

        sum += x;
        if (i & 1)
        {
            o.push_back(x);
        }
        else
        {
            e.push_back(x);
        }
    }

    ranges::sort(o, std::greater());
    ranges::sort(e, std::greater());

    i64 un = 0;
    for (int i = 0, j = 0, idx = 1, x; idx <= m; ++idx)
    {
        std::cin >> x;

        if (x & 1)
        {
            if (i < std::ssize(o) && (o[i] > 0 || (o[0] <= 0 && i == 0)))
            {
                un += o[i];
                ++i;
            }
        }
        else
        {
            if (j < std::ssize(e) && (e[j] > 0 || (e[0] <= 0 && j == 0)))
            {
                un += e[j];
                ++j;
            }
        }
    }

    std::cout << sum - un << "\n";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    std::cin >> t;
    while (t--)
    {
        solve();
    }
}
