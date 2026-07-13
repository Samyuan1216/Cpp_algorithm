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

    std::vector<int> head(n, -1), to(m << 1), next(m << 1);
    int cntg = 0;

    auto add_edge = [&](int u, int v) -> void
    {
        next[cntg] = head[u];
        to[cntg] = v;
        head[u] = cntg++;
    };

    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        add_edge(u, v);
        add_edge(v, u);
    }

    std::vector<int> dfn(n, -1), low(n);
    std::vector<bool> cut(m);
    int cntd = 0;

    for (int i = 0; i < n; ++i)
    {
        if (dfn[i] != -1)
        {
            continue;
        }

        [&](this auto &&dfs, int u, int pre) -> void
        {
            dfn[u] = low[u] = cntd++;
            for (int ei = head[u], v; ei != -1; ei = next[ei])
            {
                if ((ei ^ 1) == pre)
                {
                    continue;
                }

                v = to[ei];
                if (dfn[v] == -1)
                {
                    dfs(v, ei);

                    low[u] = std::min(low[u], low[v]);
                    if (low[v] > dfn[u])
                    {
                        cut[ei >> 1] = true;
                    }
                }
                else
                {
                    low[u] = std::min(low[u], dfn[v]);
                }
            }
        } (i, -1);
    }

    int cnt = 0;
    for (int i = 0; i < m; ++i)
    {
        if (cut[i])
        {
            ++cnt;
        }
    }

    std::cout << cnt << "\n";

    for (int i = 0; i < m; ++i)
    {
        if (cut[i])
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
