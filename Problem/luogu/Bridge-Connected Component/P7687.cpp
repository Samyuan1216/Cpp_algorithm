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
    int n, m, k, l;
    std::cin >> n >> m >> k >> l;

    std::vector<int> a(n);
    for (int i = 0, x; i < k; ++i)
    {
        std::cin >> x;
        --x;

        ++a[x];
    }

    std::vector<int> b(n);
    for (int i = 0, x; i < l; ++i)
    {
        std::cin >> x;
        --x;

        ++b[x];
    }

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
    std::vector<std::array<int, 2>> ans;
    int cntd = 0;

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
                    if (a[v] == 0 || a[v] == k || b[v] == 0 || b[v] == l)
                    {
                        ans.push_back({u, v});
                    }
                }

                a[u] += a[v];
                b[u] += b[v];
            }
            else
            {
                low[u] = std::min(low[u], dfn[v]);
            }
        }
    } (0, -1);

    std::cout << std::ssize(ans) << "\n";
    for (auto &[u, v]: ans)
    {
        std::cout << u + 1 << " " << v + 1 << "\n";
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
