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
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> g(n);
    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::vector<int> x(m), s(m);
    for (int i = 0; i < m; ++i)
    {
        std::cin >> x[i] >> s[i];
        --x[i];
    }

    std::vector<int> deep(n), father(n), son(n, -1), size(n, 1);
    [&](this auto &&dfs, int u, int f) -> void
    {
        deep[u] = deep[f] + 1;
        father[u] = f;

        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            dfs(v, u);

            size[u] += size[v];
            if (son[u] == -1 || size[son[u]] < size[v])
            {
                son[u] = v;
            }
        }
    } (0, 0);

    std::vector<i64> c(m);
    for (int i = 0; i < m; ++i)
    {
        c[i] = s[i] + deep[x[i]];
    }

    std::vector<std::vector<int>> id(n);
    for (int i = 0; i < m; ++i)
    {
        id[x[i]].push_back(i);
    }

    std::string ans(m, '1');
    std::unordered_map<i64, int, custom_hash> mp;

    auto add = [&](int i, std::vector<i64> &rubbish) -> void
    {
        if (ans[i] == '0')
        {
            return;
        }

        if (!mp.contains(c[i]))
        {
            mp[c[i]] = i;
        }
        else
        {
            if (mp[c[i]] != -1)
            {
                ans[mp[c[i]]] = '0';
                mp[c[i]] = -1;

                rubbish.push_back(c[i]);
            }

            ans[i] = '0';
        }
    };

    auto effect = [&](this auto &&dfs, int u, std::vector<i64> &rubbish) -> void
    {
        for (auto &i: id[u])
        {
            add(i, rubbish);
        }

        for (auto &v: g[u])
        {
            if (v == father[u])
            {
                continue;
            }

            dfs(v, rubbish);
        }
    };

    [&](this auto &&dfs, int u, int keep) -> void
    {
        for (auto &v: g[u])
        {
            if (v == father[u] || v == son[u])
            {
                continue;
            }

            dfs(v, 0);
        }

        if (son[u] != -1)
        {
            dfs(son[u], 1);
        }

        std::vector<i64> rubbish;
        for (auto &v: g[u])
        {
            if (v == father[u] || v == son[u])
            {
                continue;
            }

            effect(v, rubbish);
        }

        for (auto &i: id[u])
        {
            add(i, rubbish);
        }

        for (auto &v: rubbish)
        {
            mp.erase(v);
        }

        if (keep == 0)
        {
            std::unordered_map<i64, int, custom_hash>().swap(mp);
        }
    } (0, 0);

    std::cout << ans << "\n";
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
