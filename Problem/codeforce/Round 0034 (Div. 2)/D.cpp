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
    int n, r1, r2;
    std::cin >> n >> r1 >> r2;
    --r1, --r2;

    std::vector<std::vector<int>> g(n);
    for (int i = 0, f; i < n; ++i)
    {
        if (i == r1)
        {
            continue;
        }

        std::cin >> f;
        --f;

        g[i].push_back(f);
        g[f].push_back(i);
    }

    std::vector<int> ans(n);
    [&](this auto &&dfs, int u, int f) -> void
    {
        ans[u] = f;
        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            dfs(v, u);
        }
    } (r2, -1);

    for (int i = 0; i < n; ++i)
    {
        if (i == r2)
        {
            continue;
        }

        std::cout << ans[i] + 1 << " \n"[i == n - 1 || (r2 == n - 1 && i == n - 2)];
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
