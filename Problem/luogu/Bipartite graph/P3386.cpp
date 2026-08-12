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
    int n, m, e;
    std::cin >> n >> m >> e;

    std::vector<std::vector<int>> g(n);
    std::vector<int> match(m, -1);
    std::vector<bool> visited(m);

    for (int i = 0, u, v; i < e; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
    }

    auto dfs = [&](this auto &&dfs, int u) -> bool
    {
        for (auto &v: g[u])
        {
            if (visited[v])
            {
                continue;
            }

            visited[v] = true;
            if (match[v] == -1 || dfs(match[v]))
            {
                match[v] = u;
                return true;
            }
        }

        return false;
    };

    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        ranges::fill(visited, false);
        if (dfs(i))
        {
            ++ans;
        }
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
