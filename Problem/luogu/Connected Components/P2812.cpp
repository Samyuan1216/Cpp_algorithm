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
    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;
        while (x != 0)
        {
            --x;
            g[i].push_back(x);

            std::cin >> x;
        }
    }

    std::vector<int> dfn(n, -1), low(n), belong(n, -1);
    std::stack<int> sta;
    int cnt = 0, scc = 0;

    for (int i = 0; i < n; ++i)
    {
        if (dfn[i] != -1)
        {
            continue;
        }

        [&](this auto &&dfs, int u) -> void
        {
            dfn[u] = low[u] = cnt++;
            sta.push(u);

            for (auto &v: g[u])
            {
                if (dfn[v] == -1)
                {
                    dfs(v);

                    low[u] = std::min(low[u], low[v]);
                }
                else if (belong[v] == -1)
                {
                    low[u] = std::min(low[u], dfn[v]);
                }
            }

            if (int t; dfn[u] == low[u])
            {
                do
                {
                    t = sta.top();
                    sta.pop();

                    belong[t] = scc;
                } while (t != u);

                ++scc;
            }
        } (i);
    }

    std::vector<int> in(scc), out(scc);
    for (int u = 0; u < n; ++u)
    {
        for (auto &v: g[u])
        {
            if (belong[u] != belong[v])
            {
                ++out[belong[u]];
                ++in[belong[v]];
            }
        }
    }

    std::cout << ranges::count(in, 0) << "\n";
    if (scc == 1)
    {
        std::cout << 0 << "\n";
        return;
    }

    std::cout << std::max(ranges::count(in, 0), ranges::count(out, 0)) << "\n";
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
