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

class custom_hash
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
public:
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

    namespace pbds = __gnu_pbds;
    pbds::gp_hash_table<std::string, int, custom_hash> mp;
    std::vector<std::array<int, 2>> couples;

    int idx = 0;
    std::vector<std::vector<int>> g(2 * n);

    for (int i = 0; i < n; ++i)
    {
        std::string girl, boy;
        std::cin >> girl >> boy;

        if (mp.find(girl) == mp.end())
        {
            mp[girl] = idx++;
        }

        if (mp.find(boy) == mp.end())
        {
            mp[boy] = idx++;
        }

        int u = mp[girl], v = mp[boy];
        g[u].push_back(v);
        couples.push_back({u, v});
    }

    int m;
    std::cin >> m;

    for (int i = 0; i < m; ++i)
    {
        std::string girl, boy;
        std::cin >> girl >> boy;

        int u = mp[girl], v = mp[boy];
        g[v].push_back(u);
    }

    std::vector<int> dfn(2 * n, -1), low(2 * n), belong(2 * n, -1);
    std::stack<int> sta;
    int cnt = 0, scc = 0;

    for (int i = 0; i < idx; ++i)
    {
        if (dfn[i] != -1)
        {
            continue;
        }

        [&](this auto &&dfs, int u) -> void
        {
            dfn[u] = low[u] = cnt++;
            sta.push(u);

            for (auto &v: g[u])
            {
                if (dfn[v] == -1)
                {
                    dfs(v);

                    low[u] = std::min(low[u], low[v]);
                }
                else if (belong[v] == -1)
                {
                    low[u] = std::min(low[u], dfn[v]);
                }
            }

            if (int t; dfn[u] == low[u])
            {
                do
                {
                    t = sta.top();
                    sta.pop();

                    belong[t] = scc;
                } while (t != u);

                ++scc;
            }
        } (i);
    }

    for (auto &[girl, boy]: couples)
    {
        std::cout << (belong[girl] != belong[boy]? "Safe\n": "Unsafe\n");
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
