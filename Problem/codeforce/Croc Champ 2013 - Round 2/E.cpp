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
    i64 n, l, w;
    std::cin >> n >> l >> w;

    std::vector<std::vector<std::array<i64, 2>>> g(n);
    for (int i = 1, p, wi; i < n; ++i)
    {
        std::cin >> p >> wi;
        --p;

        g[p].push_back({i, wi});
        g[i].push_back({p, wi});
    }

    std::vector<int> size(n);
    std::vector<bool> visited(n);

    auto get_size = [&](this auto &&self, int u, int f) -> void
    {
        size[u] = 1;
        for (auto &[v, vw]: g[u])
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
            for (auto &[v, vw]: g[u])
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

    std::vector<std::array<i64, 2>> dist;
    auto dfs = [&](this auto &&self, int u, int f, i64 dis, i64 len) -> void
    {
        if (dis > w || len > l)
        {
            return;
        }

        dist.push_back({dis, len});
        for (auto &[v, vw]: g[u])
        {
            if (v == f || visited[v])
            {
                continue;
            }

            self(v, u, dis + vw, len + 1);
        }
    };

    auto get_ans = [&](int u, i64 dis, i64 len) -> i64
    {
        dist.clear();
        dfs(u, u, dis, len);

        ranges::sort(dist);

        BIT tr(n + 1);
        for (auto &[tw, tl]: dist)
        {
            tr.update(tl, 1);
        }

        i64 ans = 0;
        for (int left = 0, right = std::ssize(dist) - 1; left <= right;)
        {
            if (dist[left][0] + dist[right][0] <= w)
            {
                tr.update(dist[left][1], -1);
                ans += tr.query(l - dist[left][1]);

                ++left;
            }
            else
            {
                tr.update(dist[right][1], -1);

                --right;
            }
        }

        return ans;
    };

    auto divide = [&](this auto &&self, int u) -> i64
    {
        visited[u] = true;

        i64 ans = get_ans(u, 0, 0);
        for (auto &[v, vw]: g[u])
        {
            if (visited[v])
            {
                continue;
            }

            ans -= get_ans(v, vw, 1);
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
