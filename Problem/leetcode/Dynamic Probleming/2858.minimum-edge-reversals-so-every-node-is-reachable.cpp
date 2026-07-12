#include <bits/stdc++.h>
using namespace std;

// @leet start
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

class Solution
{
public:
    vector<int> minEdgeReversals(int n, vector<vector<int>>& edges)
    {
        vector<vector<int>> g(n);
        unordered_set<std::pair<int, int>, custom_hash> s;

        for (auto &e: edges)
        {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);

            s.insert({e[0], e[1]});
        }

        int cnt0 = 0;
        [&](this auto &&dfs, int u, int f) -> void
        {
            for (auto &v: g[u])
            {
                if (v == f)
                {
                    continue;
                }

                cnt0 += s.count({v, u});
                dfs(v, u);
            }
        } (0, -1);

        vector<int> ans(n);
        [&](this auto &&dfs, int u, int f, int cnt) -> void
        {
            ans[u] = cnt;
            for (auto &v: g[u])
            {
                if (v == f)
                {
                    continue;
                }

                dfs(v, u, cnt + s.count({u, v}) - s.count({v, u}));
            }
        } (0, -1, cnt0);

        return ans;
    }
};
// @leet end
