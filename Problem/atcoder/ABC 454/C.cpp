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
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> g(n);
    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;

        --u, --v;
        g[u].push_back(v);
    }

    std::vector<bool> visited(n);
    [&](this auto &&dfs, int u) -> void
    {
        visited[u] = true;

        for (auto &v: g[u])
        {
            if (visited[v])
            {
                continue;
            }

            dfs(v);
        }
    } (0);

    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        if (visited[i])
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
