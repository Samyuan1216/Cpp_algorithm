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
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> g(n);
    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    int len = 0;
    [&](this auto &&self, int u, int f, int d) -> void
    {
        if (u == n - 1)
        {
            len = d;
            return;
        }

        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            self(v, u, d + 1);
        }
    } (0, 0, 0);

    std::vector<int> dist(n);
    [&](this auto &&self, int u, int f) -> void
    {
        if (u == 0)
        {
            return;
        }

        dist[u] = dist[f] + 1;
        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            self(v, u);
        }
    } (n - 1, n - 1);

    int ans = len;
    while (m--)
    {
        int v;
        std::cin >> v;
        --v;

        ans = std::max(ans, dist[v]);
    }

    std::cout << ans << "\n";
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