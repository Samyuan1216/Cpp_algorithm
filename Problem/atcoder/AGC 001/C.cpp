#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = int64_t;

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
    int n, k;
    std::cin >> n >> k;

    auto g = std::vector(n + 1, std::vector<int>());
    auto edges = std::vector<std::pair<int, int>>();
    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;

        g[u].emplace_back(v);
        g[v].emplace_back(u);
        edges.emplace_back(u, v);
    }

    auto dfs = [&](auto &&self, int u, int f, int d, int limit) -> int
    {
        if (d > limit)
        {
            return 0;
        }

        int cnt = 1;
        for (auto &v: g[u])
        {
            if (v != f)
            {
                cnt += self(self, v, u, d + 1, limit);
            }
        }

        return cnt;
    };

    int max_keep = 0;
    if (k & 1)
    {
        int limit = (k - 1) / 2;
        for (auto &[u, v]: edges)
        {
            max_keep = std::max(max_keep, dfs(dfs, u, v, 0, limit) + dfs(dfs, v, u, 0, limit));
        }
    }
    else
    {
        int limit =  k / 2;
        for (int i = 1; i <= n; ++i)
        {
            max_keep = std::max(max_keep, dfs(dfs, i, 0, 0, limit));
        }
    }

    std::cout << n - max_keep << "\n";
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
