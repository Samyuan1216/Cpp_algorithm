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

    std::vector<std::vector<int>> g(n);
    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::vector<int> dfn(n, -1), low(n);
    std::vector<bool> cutv(n);
    int cnt = 0;

    for (int i = 0; i < n; ++i)
    {
        if (dfn[i] != -1)
        {
            continue;
        }

        [&](this auto &&self, int u, bool root) -> void
        {
            dfn[u] = low[u] = cnt++;

            int son = 0;
            for (auto &v: g[u])
            {
                if (dfn[v] == -1)
                {
                    ++son;
                    self(v, false);

                    low[u] = std::min(low[u], low[v]);
                    if (low[v] >= dfn[u])
                    {
                        if (!root || son >= 2)
                        {
                            cutv[u] = true;
                        }
                    }
                }
                else
                {
                    low[u] = std::min(low[u], dfn[v]);
                }
            }
        } (i, true);
    }

    std::cout << ranges::count(cutv, true) << "\n";
    for (int i = 0; i < n; ++i)
    {
        if (cutv[i])
        {
            std::cout << i + 1 << " ";
        }
    }
    std::cout << "\n";
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
