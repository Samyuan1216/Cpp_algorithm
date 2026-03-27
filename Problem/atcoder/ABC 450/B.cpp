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

    auto g = std::vector(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            std::cin >> g[i][j];
        }
    }

    bool status = false;
    for (int i = 0; i < n; ++i)
    {
        for (int j = i; j < n; ++j)
        {
            for (int k = i; k <= j; ++k)
            {
                if (g[i][k] + g[k][j] < g[i][j])
                {
                    status = true;
                    break;
                }
            }
        }
    }

    std::cout << (status? "Yes\n": "No\n");
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
