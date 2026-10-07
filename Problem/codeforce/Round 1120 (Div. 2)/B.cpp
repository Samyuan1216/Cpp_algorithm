#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

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
    int n, k;
    std::cin >> n >> k;

    if (k < n || k >= 2 * n)
    {
        std::cout << -1 << "\n";
        return;
    }

    std::vector g(n, std::vector<int>(n));
    int rem = k - n, num = 2, idx = 1;

    g[0][0] = 1;
    for (; rem > 0; ++idx)
    {
        g[0][idx] = num++;
        g[idx][0] = num++;
        --rem;
    }

    for (; idx < n; ++idx)
    {
        g[idx][idx] = num++;
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (g[i][j] == 0)
            {
                g[i][j] = num++;
            }
        }
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            std::cout << g[i][j] << " \n"[j == n - 1];
        }
    }
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
