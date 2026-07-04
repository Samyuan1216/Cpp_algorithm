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

    std::vector<std::array<int, 2>> edges(m);
    for (auto &[u, v]: edges)
    {
        std::cin >> u >> v;
        --u, --v;
    }

    int t;
    std::cin >> t;

    std::vector<std::vector<int>> seq;
    for (int i = 0, size; i < t; ++i)
    {
        std::cin >> size;

        seq.push_back({});
        for (int j = 0, x; j < size; ++j)
        {
            std::cin >> x;

            seq.back().push_back(x - 1);
        }
    }

    std::map<std::pair<int, int>, int> mp;
    bool is_head[m] = {};

    for (int i = 0; i < m; ++i)
    {
        mp[{edges[i][0], edges[i][1]}] = i;
        is_head[i] = true;
    }

    std::vector<int> etoe(m, -1);
    for (auto &q: seq)
    {
        int l_edge = -1, r_edge;
        for (int i = 1, u, v; i < std::ssize(q); ++i)
        {
            u = q[i - 1],  v = q[i];
            if (!mp.contains({u, v}))
            {
                std::cout << "NIE\n";
                return;
            }

            r_edge = mp[{u, v}];
            if (l_edge != -1)
            {
                if (etoe[l_edge] != -1 && etoe[l_edge] != r_edge)
                {
                    std::cout << "NIE\n";
                    return;
                }

                etoe[l_edge] = r_edge;
                is_head[r_edge] = false;
            }

            l_edge = r_edge;
        }
    }

    bool visited[m] = {};
    auto get_end = [&](int i) -> int
    {
        while (etoe[i] != -1)
        {
            if (visited[i])
            {
                return -1;
            }

            visited[i] = true;
            i = etoe[i];
        }

        return i;
    };

    std::vector<int> head(n, -1), next, to, chain_head;
    int edge_cnt = 0;

    auto add_edge = [&](int u, int v, int h) -> void
    {
        next.push_back(head[u]);
        to.push_back(v);
        chain_head.push_back(h);
        head[u] = std::ssize(next) - 1;
    };

    std::vector<int> indegree(n), outdegree(n);
    for (int i = 0; i < m; ++i)
    {
        if (!is_head[i])
        {
            continue;
        }

        auto [u, v] = edges[i];
        if (etoe[i] != -1)
        {
            int end = get_end(i);
            if (end == -1)
            {
                std::cout << "NIE\n";
                return;
            }

            v = edges[end][1];
        }

        ++outdegree[u], ++indegree[v];
        ++edge_cnt;
        add_edge(u, v, i);
    }

    for (int i = 0; i < n; ++i)
    {
        if (indegree[i] != outdegree[i])
        {
            std::cout << "NIE\n";
            return;
        }
    }

    auto cur = head;
    std::vector<int> path;

    [&](this auto &&dfs, int u, int h) -> void
    {
        for (int ei = cur[u]; ei >= 0; ei = cur[u])
        {
            cur[u] = next[ei];
            dfs(to[ei], chain_head[ei]);
        }

        path.push_back(h);
    } (0, -1);

    if (std::ssize(path) != edge_cnt + 1)
    {
        std::cout << "NIE\n";
        return;
    }

    std::vector<int> ans{0};
    for (int i = std::ssize(path) - 2; i >= 0; --i)
    {
        int e = path[i];
        while (e >= 0)
        {
            ans.push_back(edges[e][1]);
            e = etoe[e];
        }
    }

    if (std::ssize(ans) != m + 1)
    {
        std::cout << "NIE\n";
        return;
    }

    std::cout << "TAK\n";
    for (auto &x: ans)
    {
        std::cout << x + 1 << "\n";
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
