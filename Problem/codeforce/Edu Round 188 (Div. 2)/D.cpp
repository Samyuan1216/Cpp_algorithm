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

    auto g = std::vector(n + 1, std::vector<int>());
    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    int cnt1 = 0, cnt2 = 0;
    auto color = std::vector<int>(n + 1);
    auto dfs = [&](this auto &&self, int u, int f, int c) -> bool
    {
        color[u] = c;
        (c == 1? ++cnt1: ++cnt2);

        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            if (color[v] == c || (color[v] == 0 && !self(v, u, -c)))
            {
                return false;
            }
        }

        return true;
    };

    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (color[i] == 0)
        {
            cnt1 = 0, cnt2 = 0;
            if (dfs(i, 0, 1))
            {
                ans += std::max(cnt1, cnt2);
            }
        }
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
