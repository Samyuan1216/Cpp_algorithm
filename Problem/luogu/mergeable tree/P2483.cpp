#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

template<typename T>
using lim = std::numeric_limits<T>;

#ifndef YUAN_DEBUG
struct __X
{
    __X& operator<<(const auto& str) {return *this;}
    void sp([[maybe_unused]] const std::string& str = "") {}
} dout;
#define debug(x)
#endif

struct Leftist_Tree
{
    std::vector<double> cost;
    std::vector<int> to, left, right, dist;

    Leftist_Tree(): cost(1), to(1, -1), left(1), right(1), dist(1, -1) {}

    int new_node(int t, double c)
    {
        int i = std::ssize(cost);
        cost.push_back(c);
        to.push_back(t);
        left.push_back(0);
        right.push_back(0);
        dist.push_back(0);

        return i;
    }

    int clone(int i)
    {
        int idx = std::ssize(cost);
        cost.push_back(cost[i]);
        to.push_back(to[i]);
        left.push_back(left[i]);
        right.push_back(right[i]);
        dist.push_back(dist[i]);

        return idx;
    }

    int merge(int i, int j)
    {
        if (i == 0 || j == 0)
        {
            return i + j;
        }

        if (cost[i] > cost[j])
        {
            std::swap(i, j);
        }

        int h = clone(i);
        right[h] = merge(right[h], j);

        if (dist[left[h]] < dist[right[h]])
        {
            std::swap(left[h], right[h]);
        }

        dist[h] = dist[right[h]] + 1;
        return h;
    }
};

void solve()
{
    int n, m;
    double e;

    std::cin >> n >> m >> e;

    std::vector<int> ghead(n), gnext(m + 1), gto(m + 1), rhead(n), rnext(m + 1), rto(m + 1);
    std::vector<double> gweight(m + 1), rweight(m + 1);

    auto add_edge = [&](int u, int v, double w) -> void
    {
        static int cnt = 0;

        gnext[++cnt] = ghead[u];
        gto[cnt] = v;
        gweight[cnt] = w;
        ghead[u] = cnt;

        rnext[cnt] = rhead[v];
        rto[cnt] = u;
        rweight[cnt] = w;
        rhead[v] = cnt;
    };

    for (int i = 0; i < m; ++i)
    {
        int si, ti;
        double ei;

        std::cin >> si >> ti >> ei;
        --si, --ti;

        if (si != n - 1)
        {
            add_edge(si, ti, ei);
        }
    }

    auto [dist, path] = [&](int n, int s) -> std::pair<std::vector<double>, std::vector<int>>
    {
        std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> heap;

        std::vector<double> dist(n, 1e18);
        std::vector<int> path(n);
        std::vector<bool> visited(n);
    
        dist[s] = 0;
        heap.push({dist[s], s});
    
        while (!heap.empty())
        {
            auto [wu, u] = heap.top();
            heap.pop();
    
            if (visited[u])
            {
                continue;
            }
    
            visited[u] = true;
            for (int ei = rhead[u]; ei != 0; ei = rnext[ei])
            {
                int v = rto[ei];
                double wv = rweight[ei];

                if (dist[v] > wu + wv)
                {
                    dist[v] = wu + wv;
                    path[v] = ei;

                    heap.push({dist[v], v});
                }
            }
        }
    
        return {dist, path};
    } (n, n - 1);

    Leftist_Tree tr;
    std::vector<int> rt(n);

    [&]() -> void
    {
        std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> heap;
        for (int i = 0; i < n; ++i)
        {
            heap.push({dist[i], i});
        }

        while (!heap.empty())
        {
            int u = heap.top().second;
            heap.pop();

            for (int ei = ghead[u]; ei > 0; ei = gnext[ei])
            {
                int v = gto[ei];
                double wv = gweight[ei];

                if (ei != path[u])
                {
                    rt[u] = tr.merge(rt[u], tr.new_node(v, wv + dist[v] - dist[u]));
                }
            }

            if (path[u] != 0)
            {
                rt[u] = tr.merge(rt[u], rt[gto[path[u]]]);
            }
        }
    } ();

    int ans = [&]() -> int
    {
        e -= dist[0];
        if (e < 0)
        {
            return 0;
        }

        int ans = 1;
        std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> heap;

        if (rt[0] != 0)
        {
            heap.push({dist[0] + tr.cost[rt[0]], rt[0]});
        }

        while (!heap.empty())
        {
            auto [w, h] = heap.top();
            heap.pop();

            e -= w;
            if (e < 0)
            {
                break;
            }

            ++ans;
            if (tr.left[h] != 0)
            {
                heap.push({w - tr.cost[h] + tr.cost[tr.left[h]], tr.left[h]});
            }

            if (tr.right[h] != 0)
            {
                heap.push({w - tr.cost[h] + tr.cost[tr.right[h]], tr.right[h]});
            }

            if (tr.to[h] >= 0 && rt[tr.to[h]] != 0)
            {
                heap.push({w + tr.cost[rt[tr.to[h]]], rt[tr.to[h]]});
            }
        }

        return ans;
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
