#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

#ifndef YUAN_DEBUG
struct __X
{
    __X& operator<<(const auto& str) {return *this;}
    void sp([[maybe_unused]] const std::string& str = "") {}
} dout;
#define debug(x)
#endif

struct Dinic
{
    static constexpr i64 INF = 1e18;
    std::vector<int> head, next, to, limit, dist, cur;
    int cnt = 0, n;

    Dinic(int n): head(n, -1), n(n), dist(n) {}

    void add(int u, int v, int w)
    {
        next.push_back(head[u]);
        to.push_back(v);
        limit.push_back(w);
        head[u] = cnt++;

        next.push_back(head[v]);
        to.push_back(u);
        limit.push_back(0);
        head[v] = cnt++;
    }

    i64 max_flow(int s, int t)
    {
        i64 ans = 0;
        while (bfs(s, t))
        {
            ans += dfs(s, INF, t);
        }

        return ans;
    }

    bool bfs(int s, int t)
    {
        cur = head;

        ranges::fill(dist, n);
        dist[s] = 0;

        std::queue<int> q;
        q.push(s);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int ei = head[u], v, lim; ei != -1; ei = next[ei])
            {
                v = to[ei], lim = limit[ei];
                if (dist[v] == n && lim > 0)
                {
                    dist[v] = dist[u] + 1;
                    if (v == t)
                    {
                        return true;
                    }

                    q.push(v);
                }
            }
        }

        return false;
    }

    i64 dfs(int u, i64 rest, int t)
    {
        if (u == t)
        {
            return rest;
        }

        i64 flow = 0;
        for (int ei = cur[u], v, lim; ei != -1 && rest > 0; ei = next[ei])
        {
            cur[u] = ei;
            v = to[ei], lim = limit[ei];

            if (dist[u] + 1 == dist[v] && lim > 0)
            {
                i64 k = dfs(v, std::min(rest, i64(lim)), t);
                flow += k;
                rest -= k;

                limit[ei] -= k;
                limit[ei ^ 1] += k;
            }
        }

        return flow;
    }
};

void solve()
{
    int n, m;
    std::cin >> n >> m;

    int b = m + 1;
    Dinic d(n);

    for (int i = 0, s, e, c; i < m; ++i)
    {
        std::cin >> s >> e >> c;
        --s, --e;

        d.add(s, e, c * b + 1);
    }

    i64 flow = d.max_flow(0, n - 1);
    std::cout << flow / b << " " << flow % b << "\n";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    // std::cin >> t;
    while (t--)
    {
        solve();
    }
}