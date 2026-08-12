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

    std::vector<int> head(n, -1), next(m << 1), to(m << 1);
    std::vector<i64> c(m << 1);
    int cnt = 0;

    auto add_edge = [&](int u, int v, i64 w) -> void
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
        std::vector<int> d(n);
        auto bfs = [&]() -> bool
        {
            ranges::fill(d, 0);

            std::queue<int> q;
            q.push(s);

            d[s] = 1;
            while (!q.empty())
            {
                int u = q.front();
                q.pop();

                for (int ei = head[u], v; ei != -1; ei = next[ei])
                {
                    v = to[ei];
                    if (d[v] == 0 && c[ei] > 0)
                    {
                        d[v] = d[u] + 1;
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

        std::vector<int> cur;
        auto dfs = [&](this auto &&dfs, int u, i64 mf) -> i64
        {
            if (u == t)
            {
                return mf;
            }

            i64 sum = 0;
            for (int ei = cur[u], v; ei != -1; ei = next[ei])
            {
                cur[u] = ei;
                v = to[ei];

                if (d[v] == d[u] + 1 && c[ei] > 0)
                {
                    i64 f = dfs(v, std::min(mf, c[ei]));

                    c[ei] -= f;
                    c[ei ^ 1] += f;

                    sum += f;
                    mf -= f;

                    if (mf == 0)
                    {
                        break;
                    }
                }
            }

            if (sum == 0)
            {
                d[u] = 0;
            }

            return sum;
        };

        i64 flow = 0;
        while (bfs())
        {
            cur = head;
            flow += dfs(s, 1e9);
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
