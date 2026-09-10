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

    std::vector<int> head(n, -1), to(m << 1), next(m << 1), weight(m << 1);
    int cntg = 0;

    auto add_edge = [&](int u, int v, int w) -> void
    {
        next[cntg] = head[u];
        to[cntg] = v;
        weight[cntg] = w;
        head[u] = cntg++;
    };

    for (int i = 0, u, v, w; i < m; ++i)
    {
        std::cin >> u >> v >> w;
        --u, --v;

        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    int j, s;
    std::cin >> j >> s;
    --j, --s;

    std::vector<int> dfn(n, -1), low(n), belong(n);
    std::stack<int> sta;
    int cntd = 0, ebcc = 0;

    [&](this auto &&self, int u, int pre) -> void
    {
        dfn[u] = low[u] = cntd++;
        sta.push(u);

        for (int ei = head[u], v; ei != -1; ei = next[ei])
        {
            if ((ei ^ 1) == pre)
            {
                continue;
            }

            v = to[ei];
            if (dfn[v] == -1)
            {
                self(v, ei);

                low[u] = std::min(low[u], low[v]);
            }
            else
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

                belong[t] = ebcc;
            } while (t != u);

            ++ebcc;
        }
    } (0, -1);

    std::vector<std::vector<std::array<int, 2>>> g(ebcc);
    std::vector<bool> has(ebcc);

    for (int u = 0; u < n; ++u)
    {
        for (int ei = head[u], v, w; ei != -1; ei = next[ei])
        {
            v = to[ei], w = weight[ei];
            if (belong[u] != belong[v])
            {
                g[belong[u]].push_back({belong[v], w});
            }
            else
            {
                has[belong[u]] = has[belong[u]] || (w == 1? true: false);
            }
        }
    }

    if (belong[j] == belong[s])
    {
        std::cout << (has[belong[j]]? "YES\n": "NO\n");
        return;
    }

    bool status = false;
    [&](this auto &&self, int u, int f) -> bool
    {
        if (u == belong[s])
        {
            status = has[belong[s]];
            return true;
        }

        for (auto &[v, w]: g[u])
        {
            if (v == f)
            {
                continue;
            }

            if (self(v, u))
            {
                status = status || w || has[u];
                return true;
            }
        }

        return false;
    } (belong[j], belong[j]);

    std::cout << (status? "YES\n": "NO\n");
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
