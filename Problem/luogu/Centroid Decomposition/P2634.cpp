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

    std::vector<int> size(n);
    std::vector<bool> visited(n);

    auto get_size = [&](this auto &&get_size, int u, int f) -> void
    {
        size[u] = 1;
        for (auto &[v, w]: g[u])
        {
            if (v == f || visited[v])
            {
                continue;
            }

            get_size(v, u);

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

    std::array<int, 3> all, cur;
    auto dfs = [&](this auto &&dfs, int u, int f, int dis) -> void
    {
        ++cur[dis % 3];
        for (auto &[v, w]: g[u])
        {
            if (v == f || visited[v])
            {
                continue;
            }

            dfs(v, u, dis + w);
        }
    };

    auto get_ans = [&](int u) -> int
    {
        int ans = 1;
        all[0] = all[1] = all[2] = 0;

        for (auto &[v, w]: g[u])
        {
            if (visited[v])
            {
                continue;
            }

            cur[0] = cur[1] = cur[2] = 0;
            dfs(v, u, w);

            ans += (all[0] * cur[0] + all[1] * cur[2] + all[2] * cur[1] + cur[0]) * 2;
            all[0] += cur[0], all[1] += cur[1], all[2] += cur[2];
        }

        return ans;
    };

    auto divide = [&](this auto &&divide, int u) -> int
    {
        int ans = 0;
        visited[u] = true;

        ans += get_ans(u);
        for (auto &[v, w]: g[u])
        {
            if (visited[v])
            {
                continue;
            }

            ans += divide(get_root(v, u));
        }

        return ans;
    };

    int a = divide(get_root(0, 0)), b = n * n, c = std::gcd(a, b);
    std::cout << std::format("{}/{}\n", a / c, b / c);
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
