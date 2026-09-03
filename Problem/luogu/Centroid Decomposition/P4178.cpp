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

    std::vector<std::vector<std::array<int, 2>>> g(n);
    for (int i = 1, u, v, w; i < n; ++i)
    {
        std::cin >> u >> v >> w;
        --u, --v;

        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    int k;
    std::cin >> k;

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

    std::vector<int> dist;
    auto dfs = [&](this auto &&self, int u, int f, int dis) -> void
    {
        dist.push_back(dis);
        for (auto &[v, w]: g[u])
        {
            if (v == f || visited[v])
            {
                continue;
            }

            self(v, u, dis + w);
        }
    };

    auto get_ans = [&](int u, int dis) -> int
    {
        dist.clear();
        dfs(u, u, dis);

        ranges::sort(dist);

        i64 ans = 0;
        for (int l = 0, r = std::ssize(dist) - 1; l <= r;)
        {
            if (dist[l] + dist[r] <= k)
            {
                ans += r - l;
                ++l;
            }
            else
            {
                --r;
            }
        }

        return ans;
    };

    auto divide = [&](this auto &&self, int u) -> i64
    {
        visited[u] = true;

        i64 ans = get_ans(u, 0);
        for (auto &[v, w]: g[u])
        {
            if (visited[v])
            {
                continue;
            }

            ans -= get_ans(v, w);
            ans += self(get_root(v, u));
        }

        return ans;
    };

    std::cout << divide(get_root(0, 0)) << "\n";
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
