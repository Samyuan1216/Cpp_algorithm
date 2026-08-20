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
    while (true)
    {
        int u, v;
        std::cin >> u >> v;

        if (u == 0 && v == 0)
        {
            break;
        }

        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int a, b;
    std::cin >> a >> b;
    --a, --b;

    std::vector<int> dfn(n, -1), low(n);
    int cnt = 0, ans = -1;

    [&](this auto &&self, int u) -> void
    {
        dfn[u] = low[u] = cnt++;
        for (auto &v: g[u])
        {
            if (dfn[v] == -1)
            {
                self(v);

                low[u] = std::min(low[u], low[v]);
                if (low[v] >= dfn[u] && u != a && u != b && dfn[b] >= dfn[v])
                {
                    if (ans == -1 || u < ans)
                    {
                        ans = u;
                    }
                }
            }
            else
            {
                low[u] = std::min(low[u], dfn[v]);
            }
        }
    } (a);

    if (ans == -1)
    {
        std::cout << "No solution\n";
    }
    else
    {
        std::cout << ans + 1 << "\n";
    }
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
