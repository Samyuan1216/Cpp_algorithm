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
    int n, k;
    std::cin >> n >> k;

    std::vector<std::vector<std::array<int, 2>>> g(n);
    for (int i = 1, u, v, w; i < n; ++i)
    {
        std::cin >> u >> v >> w;

        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    std::vector<int> size(n);
    std::vector<bool> visited(n);

    auto get_size = [&](this auto &&self, int u, int f) -> void
    {
        size[u] = 1;
        for (auto &[v, w]: g[u])
        {
            if (v == f || visited[v])
            {
                continue;
            }

            self(v, u);

            size[u] += size[v];
        }
    };

    auto get_root = [&](int u, int f) -> int
    {
        get_size(u, f);

        int half = size[u] >> 1;
        bool find = false;

        while (!find)
        {
            find = true;
            for (auto &[v, w]: g[u])
            {
                if (v == f || visited[v] || size[v] <= half)
                {
                    continue;
                }

                f = u;
                u = v;
                find = false;

                break;
            }
        }

        return u;
    };

    auto dfs = [&](this auto &&self, int u, int f, int dis, int cnt, std::vector<std::array<int, 2>> &cur) -> void
    {
        if (dis > k)
        {
            return;
        }

        cur.push_back({dis, cnt});
        for (auto &[v, w]: g[u])
        {
            if (v == f || visited[v])
            {
                continue;
            }

            self(v, u, dis + w, cnt + 1, cur);
        }
    };

    constexpr int INF = 1e9 + 10;
    std::vector<int> dp(k + 1, INF);

    auto get_ans = [&](int u) -> int
    {
        int ans = INF;
        dp[0] = 0;

        std::vector<int> all;
        for (auto &[v, w]: g[u])
        {
            if (visited[v])
            {
                continue;
            }

            std::vector<std::array<int, 2>> cur;
            dfs(v, u, w, 1, cur);

            for (auto &x: cur)
            {
                ans = std::min(ans, dp[k - x[0]] + x[1]);
            }

            for (auto &x: cur)
            {
                all.push_back(x[0]);
                dp[x[0]] = std::min(dp[x[0]], x[1]);
            }
        }

        for (auto &x: all)
        {
            dp[x] = INF;
        }

        return ans;
    };

    auto divide = [&](this auto &&self, int u) -> int
    {
        visited[u] = true;
        int ans = get_ans(u);

        for (auto &[v, w]: g[u])
        {
            if (visited[v])
            {
                continue;
            }

            ans = std::min(ans, self(get_root(v, u)));
        }

        return ans;
    };

    int ans = divide(get_root(0, 0));
    std::cout << (ans == INF? -1: ans) << "\n";
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
