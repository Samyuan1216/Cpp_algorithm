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
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    --s, --t;

    std::vector<int> head(n, -1), next(m << 1), to(m << 1), c(m << 1);
    int cnt = 0;

    auto add_edge = [&](int u, int v, int w) -> void
    {
        next[cnt] = head[u];
        to[cnt] = v;
        c[cnt] = w;
        head[u] = cnt++;
    };

    for (int i = 0, u, v, w; i < m; ++i)
    {
        std::cin >> u >> v >> w;
        --u, --v;

        add_edge(u, v, w);
        add_edge(v, u, 0);
    }

    i64 ans = [&]() -> i64
    {
        std::vector<int> max_flow(n), pre(n);
        auto bfs = [&]() -> bool
        {
            ranges::fill(max_flow, 0);
            max_flow[s] = 2e9;

            std::queue<int> q;
            q.push(s);

            while (!q.empty())
            {
                int u = q.front();
                q.pop();

                for (int ei = head[u], v; ei != -1; ei = next[ei])
                {
                    v = to[ei];
                    if (max_flow[v] == 0 && c[ei] > 0)
                    {
                        max_flow[v] = std::min(max_flow[u], c[ei]);
                        pre[v] = ei;

                        q.push(v);
                        if (v == t)
                        {
                            return true;
                        }
                    }
                }
            }

            return false;
        };

        i64 flow = 0;
        while (bfs())
        {
            int v = t;
            while (v != s)
            {
                int ei = pre[v];
                c[ei] -= max_flow[t];
                c[ei ^ 1] += max_flow[t];

                v = to[ei ^ 1];
            }

            flow += max_flow[t];
        }

        return flow;
    } ();

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
