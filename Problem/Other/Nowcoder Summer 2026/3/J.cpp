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
    int n, q;
    std::cin >> n >> q;

    std::vector<std::vector<int>> g(n);
    for (int i = 1, p; i < n; ++i)
    {
        std::cin >> p;
        --p;

        g[p].push_back(i);
    }

    std::vector<int> deep(n);
    [&](this auto &&dfs, int u, int f) -> void
    {
        deep[u] = (u == 0? 0: deep[f] + 1);
        for (auto &v: g[u])
        {
            dfs(v, u);
        }
    } (0, 0);

    namespace pbds = __gnu_pbds;
    std::vector<pbds::priority_queue<std::pair<int, int>>> need(n);

    while (q--)
    {
        int u, v;
        std::cin >> u >> v;
        --u, --v;

        need[u].push({deep[v], v});
    }

    std::vector<int> new_p(n);
    [&](this auto &&dfs, int u) -> void
    {
        for (auto &v: g[u])
        {
            dfs(v);
        }

        if (need[u].empty())
        {
            new_p[u] = 0;
            return;
        }

        auto [d, v] = need[u].top();
        while (!need[u].empty() && v == need[u].top().second)
        {
            need[u].pop();
        }

        new_p[u] = v;
        need[v].join(need[u]);
    } (0);

    std::vector<std::vector<int>> g2(n);
    for (int i = 1; i < n; ++i)
    {
        g2[new_p[i]].push_back(i);
    }

    int ans = 0;
    [&](this auto &&dfs, int u, int d) -> void
    {
        ans += d;
        for (auto &v: g2[u])
        {
            dfs(v, d + 1);
        }
    } (0, 0);

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
