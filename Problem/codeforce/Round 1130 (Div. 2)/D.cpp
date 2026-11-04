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
    int k;
    std::cin >> k;

    int ri = -1, ru = -1;
    for (int i = 1; i <= k; ++i)
    {
        int n;
        std::cin >> n;

        if (n == 1)
        {
            continue;
        }

        std::vector<std::vector<int>> g(n);
        std::vector<int> degree(n);

        for (int j = 1, u, v; j < n; ++j)
        {
            std::cin >> u >> v;
            --u, --v;

            g[u].push_back(v);
            g[v].push_back(u);

            ++degree[u], ++degree[v];
        }

        for (int j = 0; j < n; ++j)
        {
            if (degree[j] == 1)
            {
                if (ri == -1)
                {
                    ri = i;
                    ru = g[j][0];
                }
            }
        }
    }

    if (ri == -1)
    {
        ri = 1;
        ru = 0;
    }

    for (int i = 1; i <= k; ++i)
    {
        if (i == ri)
        {
            continue;
        }

        std::cout << std::format("{} {} {} {}\n", ri, ru + 1, i, 1);
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