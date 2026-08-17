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

    std::vector<std::vector<std::array<int, 2>>> g(n);
    for (int i = 1, u, v, w; i < n; ++i)
    {
        std::cin >> u >> v >> w;
        --u, --v;

        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    std::vector<int> query(m);
    for (auto &x: query)
    {
        std::cin >> x;
    }

    int max = *ranges::max_element(query);

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

    auto dfs = [&](this auto &&self, int u, int f, int dis, std::vector<int> &cur) -> void
    {
        if (dis > max)
        {
            return;
        }

        cur.push_back(dis);
        for (auto &[v, w]: g[u])
        {
            if (v == f || visited[v])
            {
                continue;
            }

            self(v, u, dis + w, cur);
        }
    };

    constexpr int MAXV = 1e7 + 10;
    std::bitset<MAXV> exist;
    std::vector<bool> ans(m);

    auto get_ans = [&](int u) -> void
    {
        std::vector<int> all;
        exist[0] = 1;

        for (auto &[v, w]: g[u])
        {
            if (visited[v])
            {
                continue;
            }

            std::vector<int> cur;
            dfs(v, u, w, cur);

            for (int i = 0; i < m; ++i)
            {
                for (auto &x: cur)
                {
                    if (ans[i])
                    {
                        break;
                    }

                    if (query[i] - x >= 0)
                    {
                        ans[i] = ans[i] || exist[query[i] - x];
                    }
                }
            }

            for (auto &x: cur)
            {
                all.push_back(x);
                exist[x] = 1;
            }
        }

        for (auto &x: all)
        {
            exist[x] = 0;
        }
    };

    auto divide = [&](this auto &&self, int u) -> void
    {
        visited[u] = true;
        get_ans(u);

        for (auto &[v, w]: g[u])
        {
            if (visited[v])
            {
                continue;
            }

            self(get_root(v, u));
        }
    };

    divide(get_root(0, 0));
    for (int i = 0; i < m; ++i)
    {
        std::cout << (ans[i]? "AYE\n": "NAY\n");
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
