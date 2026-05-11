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
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<int, i64>>> g(n);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        i64 w;
        std::cin >> u >> v >> w;
        --u, --v;

        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    std::vector<bool> p(n);
    for (int i = 0, x; i < m; ++i)
    {
        std::cin >> x;
        --x;

        p[x] = true;
    }

    i64 ans = 0;
    auto dfs = [&](auto &&dfs, int u, int f) -> i64
    {
        i64 uc = 0;
        bool status = false;

        for (auto &[v, w]: g[u])
        {
            if (v == f)
            {
                continue;
            }

            status = true;

            i64 vc = dfs(dfs, v, u);
            ans += (vc - 1) * w;
            uc += vc;
        }

        if (!status)
        {
            uc = 1;
        }

        if (p[u])
        {
            return 1;
        }

        return uc;
    };

    dfs(dfs, 0, -1);

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
