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

    std::vector<int> head(n, -1), next(m << 1), to(m << 1);
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
    std::vector<std::vector<int>> ebcc;
    std::stack<int> sta;
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
                    dfs(v, ei);

                    low[u] = std::min(low[u], low[v]);
                }
                else
                {
                    low[u] = std::min(low[u], dfn[v]);
                }
            }

            if (int t; dfn[u] == low[u])
            {
                ebcc.push_back({});
                do
                {
                    t = sta.top();
                    sta.pop();

                    ebcc.back().push_back(t);
                } while (t != u);
            }
        } (i, -1);
    }

    std::cout << std::ssize(ebcc) << "\n";
    for (auto &v: ebcc)
    {
        std::cout << std::ssize(v);
        for (auto &x: v)
        {
            std::cout << " " << x + 1;
        }
        std::cout << "\n";
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
