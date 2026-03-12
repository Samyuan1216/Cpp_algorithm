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
    int n;
    std::cin >> n;

    auto g = std::vector(n + 1, std::vector<std::pair<int, int>>());
    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;

        g[u].push_back({v, 1});
        g[v].push_back({u, 1});
    }

    int diameter = 0;
    auto dist = std::vector<int>(n + 1);
    auto tree_diameter = [&](auto &&self, int u, int f) -> void
    {
        for (auto &[v, w]: g[u])
        {
            if (v != f)
            {
                self(self, v, u);
            }
        }
    
        for (auto &[v, w]: g[u])
        {
            if (v != f)
            {
                diameter = std::max(diameter, dist[u] + dist[v] + w);
                dist[u] = std::max(dist[u], dist[v] + w);
            }
        }
    };

    tree_diameter(tree_diameter, 1, 0);
    std::cout << diameter << "\n";
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
