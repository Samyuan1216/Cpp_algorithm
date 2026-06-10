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

    std::vector<std::vector<std::array<int, 3>>> g1(n);
    for (int i = 0; i < m; ++i)
    {
        int u, v, cnt;
        double k;
        std::cin >> u >> v >> cnt >> k;
        --u, --v;

        g1[u].push_back({v, cnt, (int)std::round(10 * k)});
    }

    std::vector<int> dfn(n, -1), low(n), belong(n, -1);
    std::vector<std::vector<int>> scc;
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

            for (auto &[v, cnt, k]: g1[u])
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
                scc.push_back({});
                do
                {
                    t = sta.top();
                    sta.pop();

                    belong[t] = std::ssize(scc) - 1;
                    scc.back().push_back(t);
                } while (t != u);
            }
        } (i);
    }

    std::vector<int> degree(std::ssize(scc)), weight(std::ssize(scc));
    std::vector<std::vector<std::array<int, 2>>> g2(std::ssize(scc));

    for (int u = 0; u < n; ++u)
    {
        for (auto &[v, cnt, k]: g1[u])
        {
            if (belong[u] == belong[v])
            {
                while (cnt > 0)
                {
                    weight[belong[u]] += cnt;
                    cnt = (1ll * cnt * k) / 10;
                }
            }
            else
            {
                g2[belong[u]].push_back({belong[v], cnt});
                ++degree[belong[v]];
            }
        }
    }

    int s;
    std::cin >> s;
    --s;

    std::vector<int> dp(std::ssize(scc), -1);
    dp[belong[s]] = weight[belong[s]];

    std::queue<int> q;
    for (int i = 0; i < std::ssize(scc); ++i)
    {
        if (degree[i] == 0)
        {
            q.push(i);
        }
    }

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto &[v, w]: g2[u])
        {
            if (dp[u] != -1)
            {
                dp[v] = std::max(dp[v], dp[u] + w + weight[v]);
            }

            if (--degree[v] == 0)
            {
                q.push(v);
            }
        }
    }

    std::cout << *ranges::max_element(dp) << "\n";
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
