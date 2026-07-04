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
    i64 n, m, x;
    std::cin >> n >> m >> x;

    std::vector<std::vector<int>> g1(n);
    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g1[u].push_back(v);
    }

    std::vector<int> dfn(n, -1), low(n), belong(n, -1), scc;
    std::stack<int> sta;
    int cnt = 0;

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

            for (auto &v: g1[u])
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
                scc.push_back(0);
                do
                {
                    t = sta.top();
                    sta.pop();

                    belong[t] = std::ssize(scc) - 1;
                    ++scc.back();
                } while (t != u);
            }
        } (i);
    }

    std::vector<std::vector<int>> g2(std::ssize(scc));
    for (int u = 0; u < n; ++u)
    {
        for (auto &v: g1[u])
        {
            if (belong[u] == belong[v])
            {
                continue;
            }

            g2[belong[u]].push_back(belong[v]);
        }
    }

    std::vector<int> in(std::ssize(scc));
    for (int i = 0; i < std::ssize(scc); ++i)
    {
        ranges::sort(g2[i]);
        auto [l, r] = ranges::unique(g2[i]);
        g2[i].erase(l, r);

        for (auto &v: g2[i])
        {
            ++in[v];
        }
    }

    std::vector<i64> dpsum(std::ssize(scc)), dpcnt(std::ssize(scc));
    std::queue<int> q;

    for (int i = 0; i < std::ssize(scc); ++i)
    {
        if (in[i] == 0)
        {
            q.push(i);

            dpsum[i] = scc[i];
            dpcnt[i] = 1;
        }
    }

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto &v: g2[u])
        {
            if (dpsum[u] + scc[v] > dpsum[v])
            {
                dpsum[v] = dpsum[u] + scc[v];
                dpcnt[v] = dpcnt[u];
            }
            else if (dpsum[u] + scc[v] == dpsum[v])
            {
                dpcnt[v] = (dpcnt[v] + dpcnt[u]) % x;
            }

            if (--in[v] == 0)
            {
                q.push(v);
            }
        }
    }

    i64 ans = 0, max = *ranges::max_element(dpsum);
    for (int i = 0; i < std::ssize(scc); ++i)
    {
        if (dpsum[i] == max)
        {
            ans = (ans + dpcnt[i]) % x;
        }
    }

    std::cout << max << "\n";
    std::cout << ans << "\n";
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
