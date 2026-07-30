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

struct custom_hash
{
    using u64 = uint64_t;
    static u64 splitmix64(u64 x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;

        return x ^ (x >> 31);
    }

    static u64 rng()
    {
        static const u64 FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return FIXED_RANDOM;
    }

    template<std::integral T>
    size_t operator()(T x) const
    {
        return splitmix64(static_cast<u64>(x) + rng());
    }

    size_t operator()(const std::string &s) const
    {
        u64 h = rng();
        for (unsigned char c: s)
        {
            h = splitmix64(h + c);
        }

        return h;
    }

    template<class A, class B>
    size_t operator()(const std::pair<A, B> &p) const
    {
        u64 h = rng();
        h = splitmix64(h + (*this)(p.first));
        h = splitmix64(h + (*this)(p.second));

        return h;
    }

    template<class... Ts>
    size_t operator()(const std::tuple<Ts...> &t) const
    {
        u64 h = rng();
        std::apply([&](const auto&... args)
        {
            ((h = splitmix64(h + (*this)(args))), ...);
        }, t);

        return h;
    }
};

void solve()
{
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> g(n);
    std::vector<int> name(n), root;
    std::unordered_map<std::string, int, custom_hash> mp;

    for (int i = 0, r, cnt = 0; i < n; ++i)
    {
        std::string str;
        std::cin >> str >> r;
        --r;

        if (mp.contains(str))
        {
            name[i] = mp[str];
        }
        else
        {
            name[i] = mp[str] = cnt++;
        }

        if (r == -1)
        {
            root.push_back(i);
        }
        else
        {
            g[r].push_back(i);
        }
    }

    int m = 0;
    std::cin >> m;

    std::vector<std::vector<std::array<int, 2>>> q(n);
    for (int id = 0, v, k; id < m; ++id)
    {
        std::cin >> v >> k;
        --v;

        q[v].push_back({k, id});
    }

    std::vector<int> ans(m), size(n, 1), son(n, -1);
    for (auto &s: root)
    {
        int depth = 0;
        [&](this auto &&dfs, int u, int d) -> void
        {
            depth = std::max(depth, d);
            for (auto &v: g[u])
            {
                dfs(v, d + 1);

                size[u] += size[v];
                if (son[u] == -1 || size[son[u]] < size[v])
                {
                    son[u] = v;
                }
            }
        } (s, 0);

        std::vector<std::unordered_set<int>> deep(depth + 1);
        auto effect = [&](this auto &&dfs, int u, int d) -> void
        {
            deep[d].insert(name[u]);
            for (auto &v: g[u])
            {
                dfs(v, d + 1);
            }
        };

        auto cancel = [&](this auto &&dfs, int u, int d) -> void
        {
            deep[d].clear();
            for (auto &v: g[u])
            {
                dfs(v, d + 1);
            }
        };

        [&](this auto &&dfs, int u, int d, int keep) -> void
        {
            for (auto &v: g[u])
            {
                if (v == son[u])
                {
                    continue;
                }

                dfs(v, d + 1, 0);
            }

            if (son[u] != -1)
            {
                dfs(son[u], d + 1, 1);
            }

            for (auto &v: g[u])
            {
                if (v == son[u])
                {
                    continue;
                }

                effect(v, d + 1);
            }

            deep[d].insert(name[u]);
            for (auto &[k, id]: q[u])
            {
                if (d + k <= depth)
                {
                    ans[id] = std::ssize(deep[d + k]);
                }
            }

            if (keep == 0)
            {
                cancel(u, d);
            }
        } (s, 0, 0);
    }

    for (auto &x: ans)
    {
        std::cout << x << "\n";
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
