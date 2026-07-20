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
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> g(n);
    std::vector<int> to(n);

    for (int i = 0, p; i < n; ++i)
    {
        std::cin >> p;
        --p;

        to[i] = p;
        g[p].push_back(i);
    }

    std::vector<int> status(n), from(n);
    std::vector<bool> cycle(n);

    for (int i = 0; i < n; ++i)
    {
        if (status[i] != 0)
        {
            continue;
        }

        [&](this auto &&dfs, int u) -> bool
        {
            status[u] = 1;
            bool find = false;

            for (auto &v: g[u])
            {
                if (status[v] == 0)
                {
                    from[v] = u;
                    if (dfs(v))
                    {
                        find = true;
                    }
                }
                else if (status[v] == 1)
                {
                    cycle[v] = true;
                    for (int i = u; i != v; i = from[i])
                    {
                        cycle[i] = true;
                    }

                    find = true;
                }

                if (find)
                {
                    break;
                }
            }

            status[u] = 2;
            return find;
        } (i);
    }

    auto dp = std::vector(n, std::vector<int>(2));
    auto tree_dp = [&](this auto &&dfs, int u) -> void
    {
        dp[u][1] = 1;
        for (auto &v: g[u])
        {
            if (cycle[v])
            {
                continue;
            }

            dfs(v);

            dp[u][0] += std::max(dp[v][0], dp[v][1]);
            dp[u][1] += dp[v][0];
        }
    };

    std::vector<bool> visited(n);
    int ans = 0;

    for (int i = 0; i < n; ++i)
    {
        if (!cycle[i] || visited[i])
        {
            continue;
        }

        std::vector<int> c;

        int u = i;
        while (!visited[u])
        {
            visited[u] = true;
            c.push_back(u);
            u = to[u];
        }

        for (auto &u: c)
        {
            tree_dp(u);
        }

        int k = std::ssize(c), cur = 0;
        auto f = std::vector(k, std::vector<int>(2));

        constexpr int INF = -1e9;
        f[0][0] = dp[c[0]][0];
        f[0][1] = INF;

        for (int j = 1; j < k; ++j)
        {
            f[j][0] = std::max(f[j - 1][0], f[j - 1][1]) + dp[c[j]][0];
            f[j][1] = f[j - 1][0] + dp[c[j]][1];
        }

        cur = std::max(f[k - 1][0], f[k - 1][1]);

        f[0][0] = INF;
        f[0][1] = dp[c[0]][1];

        for (int j = 1; j < k; ++j)
        {
            f[j][0] = std::max(f[j - 1][0], f[j - 1][1]) + dp[c[j]][0];
            f[j][1] = f[j - 1][0] + dp[c[j]][1];
        }

        cur = std::max(cur, f[k - 1][0]);
        ans += cur;
    }

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
