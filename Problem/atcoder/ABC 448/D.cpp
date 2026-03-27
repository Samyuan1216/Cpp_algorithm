#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

template<typename T>
using lim = std::numeric_limits<T>;

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

template<typename T1, typename T2 = __gnu_pbds::null_type>
using hash_table = __gnu_pbds::gp_hash_table<T1, T2, custom_hash>;

void solve()
{
    int n;
    std::cin >> n;

    auto arr = std::vector<int>(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];
    }

    auto g = std::vector(n + 1, std::vector<int>());
    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    auto s = hash_table<int, int>();
    auto ans = std::vector<bool>(n + 1);
    auto dfs = [&](this auto &&self, int u, int f, bool status) -> void
    {
        if (status || s[arr[u]] > 0)
        {
            ans[u] = status = true;
        }

        ++s[arr[u]];
        for (auto &v: g[u])
        {
            if (v != f)
            {
                self(v, u, status);
            }
        }

        --s[arr[u]];
    };

    dfs(1, 0, false);

    for (int i = 1; i <= n; ++i)
    {
        std::cout << (ans[i]? "Yes\n": "No\n");
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
