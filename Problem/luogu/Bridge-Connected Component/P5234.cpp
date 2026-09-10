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
    for (int u = 0; u < n; ++u)
    {
        for (int ei = head[u], v, w; ei != -1; ei = next[ei])
        {
            v = to[ei], w = weight[ei];
            if (belong[u] == belong[v])
            {
                continue;
            }

            if (u >= v)
            {
                continue;
            }

            g[belong[u]].push_back({belong[v], w});
            g[belong[v]].push_back({belong[u], w});
        }
    }

    auto check = [&](int mid) -> bool
    {
        int diameter = 0, total = 0;
        std::vector<int> dist(ebcc);

        [&](this auto &&self, int u, int f) -> void
        {
            for (auto &[v, w]: g[u])
            {
                if (v == f)
                {
                    continue;
                }

                total += (w <= mid? 1: 0);
                self(v, u);
            }
        
            for (auto &[v, w]: g[u])
            {
                if (v == f)
                {
                    continue;
                }

                diameter = std::max(diameter, dist[u] + dist[v] + (w <= mid? 1: 0));
                dist[u] = std::max(dist[u], dist[v] + (w <= mid? 1: 0));
            }
        } (0, 0);

        return diameter < total;
    };

    auto find = [&](auto l, auto r, bool find_first = true) -> std::optional<decltype(l)>
    {
        std::optional<decltype(l)> ans;
        while (l <= r)
        {
            auto mid = std::midpoint(l, r);
            if (check(mid))
            {
                ans = mid;
                find_first? (r = mid - 1): (l = mid + 1);
            }
            else
            {
                find_first? (l = mid + 1): (r = mid - 1);
            }
        }
    
        return ans;
    };

    auto ans = find(1, int(1e9));
    std::cout << (ans? *ans: -1) << "\n";
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
