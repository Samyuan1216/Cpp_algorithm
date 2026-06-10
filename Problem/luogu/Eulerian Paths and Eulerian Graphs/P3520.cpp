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

    std::vector<int> head(n, -1), next(m << 1, -1), to(m << 1, -1);
    int cnt = 0;

    auto add_edge = [&](int u, int v) -> void
    {
        next[cnt] = head[u];
        to[cnt] = v;
        head[u] = cnt++;
    };

    std::vector<int> degree(n);
    for (int i = 0, u, v, s, t; i < m; ++i)
    {
        std::cin >> u >> v >> s >> t;
        --u, --v;

        if (s == t)
        {
            continue;
        }

        ++degree[u], ++degree[v];
        add_edge(u, v);
        add_edge(v, u);
    }

    bool check = true;
    for (int i = 0; i < n; ++i)
    {
        if (degree[i] & 1)
        {
            check = false;
            break;
        }
    }

    if (!check)
    {
        std::cout << "NIE\n";
        return;
    }

    std::vector<bool> visnode(n), visedge(m), inpath(n);
    std::stack<int> path;
    std::vector<std::vector<int>> ans;
    auto cur = head;

    for (int i = 0; i < n; ++i)
    {
        if (visnode[i])
        {
            continue;
        }

        [&](this auto &&dfs, int u) -> void
        {
            visnode[u] = true;
            for (int ei = cur[u]; ei != -1; ei = cur[u])
            {
                cur[u] = next[ei];
                if (visedge[ei >> 1])
                {
                    continue;
                }

                visedge[ei >> 1] = true;
                dfs(to[ei]);
            }

            if (inpath[u])
            {
                ans.push_back({});
                ans.back().push_back(u);

                while (path.top() != u)
                {
                    ans.back().push_back(path.top());
                    inpath[path.top()] = false;
                    path.pop();
                }

                ans.back().push_back(u);
                path.pop();
            }

            path.push(u);
            inpath[u] = true;
        } (i);
    }

    std::cout << std::ssize(ans) << "\n";
    for (auto &arr: ans)
    {
        std::cout << std::ssize(arr) - 1 << " ";
        for (int i = 0; i < std::ssize(arr); ++i)
        {
            std::cout << arr[i] + 1 << " \n"[i == std::ssize(arr) - 1];
        }
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
