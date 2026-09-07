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

template<typename T = int, typename F = std::plus<T>>
struct BIT
{
    int n;
    T init;
    F compute;
    std::vector<T> tree;

    static constexpr int lowbit(int i)
    {
        return i & -i;
    }

    BIT(int size, F func = F{}, T i = T{}): n(size), init(i), compute(func), tree(size + 1, i) {}

    void update(int i, T v)
    {
        ++i;
        while (i <= n)
        {
            tree[i] = compute(tree[i], v);
            i += lowbit(i);
        }
    }

    T query(int i)
    {
        ++i;
        T ans = init;
        while (i > 0)
        {
            ans = compute(ans, tree[i]);
            i -= lowbit(i);
        }

        return ans;
    }
};

void solve()
{
    int n, llim, rlim;
    std::cin >> n >> llim >> rlim;

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

    std::vector<std::array<int, 2>> arr;
    auto dfs = [&](this auto &&self, int u, int f, int d, int max) -> void
    {
        if (d > rlim)
        {
            return;
        }

        arr.push_back({max, d});

        for (auto &[v, w]: g[u])
        {
            if (v == f || visited[v])
            {
                continue;
            }

            self(v, u, d + 1, std::max(max, w));
        }
    };

    BIT tr(n + 1);
    auto get_ans = [&](int u, int d, int max) -> i64
    {
        arr.clear();
        dfs(u, u, d, max);

        ranges::sort(arr);

        i64 ans = 0;
        for (auto &[val, len]: arr)
        {
            ans += 1ll * val * (tr.query(rlim - len) - tr.query(llim - len - 1));
            tr.update(len, 1);
        }

        for (auto &[val, len]: arr)
        {
            tr.update(len, -1);
        }

        return ans;
    };

    auto divide = [&](this auto &&self, int u) -> i64
    {
        visited[u] = true;

        i64 ans = get_ans(u, 0, 0);
        for (auto &[v, w]: g[u])
        {
            if (visited[v])
            {
                continue;
            }

            ans -= get_ans(v, 1, w);
            ans += self(get_root(v, u));
        }

        return ans;
    };

    std::cout << 2 * divide(get_root(0, 0)) << "\n";
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
