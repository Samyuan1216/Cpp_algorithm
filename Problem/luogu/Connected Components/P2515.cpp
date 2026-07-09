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

    std::vector<int> weight(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> weight[i];
    }

    std::vector<int> value(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> value[i];
    }

    std::vector<std::vector<int>> g1(n + 1);

    for (int i = 1, p; i <= n; ++i)
    {
        std::cin >> p;

        g1[p].push_back(i);
    }

    std::vector<int> dfn1(n + 1, -1), low(n + 1), belong(n + 1, -1), w, v;
    std::stack<int> sta;
    int scc = 0, cnt = 0;

    for (int i = 0; i <= n; ++i)
    {
        if (dfn1[i] != -1)
        {
            continue;
        }

        [&](this auto &&dfs, int u) -> void
        {
            dfn1[u] = low[u] = cnt++;
            sta.push(u);

            for (auto &v: g1[u])
            {
                if (dfn1[v] == -1)
                {
                    dfs(v);

                    low[u] = std::min(low[u], low[v]);
                }
                else if (belong[v] == -1)
                {
                    low[u] = std::min(low[u], dfn1[v]);
                }
            }

            if (int t; dfn1[u] == low[u])
            {
                w.push_back({}), v.push_back({});
                do
                {
                    t = sta.top();
                    sta.pop();

                    belong[t] = scc;
                    w.back() += weight[t];
                    v.back() += value[t];
                } while (t != u);

                ++scc;
            }
        } (i);
    }

    int s = belong[0];
    std::vector<std::vector<int>> g2(scc);
    std::vector<int> in(scc);

    for (int u = 0; u <= n; ++u)
    {
        for (auto &v: g1[u])
        {
            if (belong[u] == belong[v])
            {
                continue;
            }

            g2[belong[u]].push_back(belong[v]);
            ++in[belong[v]];
        }
    }

    for (int i = 0; i < scc; ++i)
    {
        if (i != s && in[i] == 0)
        {
            g2[s].push_back(i);
        }
    }

    std::vector<int> size(scc), nw(scc), nv(scc);
    cnt = 0;

    [&](this auto &&dfs, int u) -> int
    {
        int cur = cnt++;
        nw[cur] = w[u];
        nv[cur] = v[u];

        int sz = 1;
        for (auto &v: g2[u])
        {
            sz += dfs(v);
        }

        size[cur] = sz;
        return sz;
    } (s);

    auto flat_index = [](auto ...D)
    {
        return [=](auto ...i)
        {
            int idx = 0;
            ((idx = idx * D + i), ...);
    
            return idx;
        };
    };
    auto idx = flat_index(scc + 1, m + 1);

    std::vector<int> dp((scc + 1) * (m + 1));
    for (int i = scc - 1; i >= 1; --i)
    {
        for (int j = 0; j <= m; ++j)
        {
            dp[idx(i, j)] = dp[idx(i + size[i], j)];
            if (j >= nw[i])
            {
                dp[idx(i, j)] = std::max(dp[idx(i, j)], nv[i] + dp[idx(i + 1, j - nw[i])]);
            }
        }
    }

    std::cout << dp[idx(1, m)] << "\n";
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
