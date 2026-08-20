// https://loj.ac/p/10103

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

void solve(int n, int m)
{
    std::vector<std::vector<int>> g(n);
    for (int i = 0, u, v; i < m ; ++i)
    {
        std::cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::vector<int> dfn(n, -1), low(n);
    int cnt = 0, block = 0, ans = 0;

    for (int i = 0; i < n; ++i)
    {
        if (dfn[i] != -1)
        {
            continue;
        }

        ++block;
        [&](this auto &&self, int u, bool root) -> void
        {
            dfn[u] = low[u] = cnt++;
            int son = 0, cut = 0;

            for (auto &v: g[u])
            {
                if (dfn[v] == -1)
                {
                    ++son;
                    self(v, false);

                    low[u] = std::min(low[u], low[v]);
                    if (low[v] >= dfn[u] && !root)
                    {
                        ++cut;
                    }
                }
                else
                {
                    low[u] = std::min(low[u], dfn[v]);
                }
            }

            if (root)
            {
                ans = std::max(ans, son);
            }
            else
            {
                ans = std::max(ans, cut + 1);
            }
        } (i, true);
    }

    std::cout << block + (ans - 1) << "\n";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    while (true)
    {
        int n, m;
        std::cin >> n >> m;

        if (n == 0 && m == 0)
        {
            break;
        }

        solve(n, m);
    }
}
