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

    std::vector<std::vector<int>> g(n);
    std::vector<int> indegree(n);

    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
        ++indegree[v];
    }

    std::vector<int> dp(n);
    std::queue<int> q;

    for (int i = 0; i < n; ++i)
    {
        if (indegree[i] == 0)
        {
            dp[i] = 1;
            q.push(i);
        }
    }

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto &v: g[u])
        {
            dp[v] = std::max(dp[v], dp[u] + 1);
            if (--indegree[v] == 0)
            {
                q.push(v);
            }
        }
    }

    std::cout << *ranges::max_element(dp) - 1 << "\n";
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
