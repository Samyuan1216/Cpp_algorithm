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
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> g(n);
    std::vector<int> degree(n);

    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
        g[v].push_back(u);
        ++degree[u], ++degree[v];
    }

    std::queue<int> q;
    for (int i = 0; i < n; ++i)
    {
        if (degree[i] == 1)
        {
            q.push(i);
        }
    }

    auto dfs = [&](this auto &&self, int u, int f, int d) -> int
    {
        if (d > 2)
        {
            if (degree[u] == 1)
            {
                q.push(u);
            }

            return 0;
        }

        int num = 1;
        for (auto &v: g[u])
        {
            if (degree[v] == 0 || v == f)
            {
                continue;
            }

            --degree[u], --degree[v];
            num += self(v, u, d + 1);
        }

        return num;
    };

    std::vector<int> ans;
    while (!q.empty())
    {
        auto u = q.front();
        q.pop();

        if (degree[u] == 0)
        {
            continue;
        }

        ans.push_back(dfs(u, u, 0) - 1);
    }

    ranges::sort(ans);
    for (int i = 0; i < std::ssize(ans); ++i)
    {
        std::cout << ans[i] << " \n"[i == std::ssize(ans) - 1];
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
