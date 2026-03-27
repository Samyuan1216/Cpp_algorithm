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
    int n;
    std::cin >> n;

    auto g = std::vector(n + 1, std::vector<int>());
    auto degree = std::vector<int>(n + 1);

    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;

        ++degree[u], ++degree[v];
        g[u].push_back(v);
        g[v].push_back(u);
    }

    struct Info
    {
        int max_len = 0;
        int len = 0;
    };

    auto dfs = [&](this auto &&self, int u, int f) -> Info
    {
        Info infou;

        int max = 0, submax = 0;
        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            auto infov = self(v, u);

            infou.max_len = std::max(infou.max_len, infov.max_len);
            if (infov.len >= max)
            {
                submax = max;
                max = infov.len;
            }
            else if (infov.len > submax)
            {
                submax = infov.len;
            }
        }

        if (degree[u] > 3)
        {
            infou.len = max + 1;
            infou.max_len = std::max(infou.max_len, max + submax + 1);
        }
        else if (degree[u] == 3)
        {
            infou.len = 1;
            infou.max_len = std::max(infou.max_len, max + 1);
        }
        else if (degree[u] == 2)
        {
            infou.max_len = std::max(infou.max_len, 1);
        }

        return infou;
    };

    std::cout << dfs(1, 0).max_len << "\n";
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
