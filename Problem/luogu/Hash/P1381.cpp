#include <bits/stdc++.h>
#include <bits/extc++.h>
namespace ranges = std::ranges;
namespace views = std::views;

using i64 = int64_t;

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

    hash_table<std::string, int> mp;
    for (int i = 0; i < n; ++i)
    {
        std::string str;
        std::cin >> str;

        mp[str] = 0;
    }

    int m;
    std::cin >> m;

    std::vector<std::string> arr(m);
    for (int i = 0; i < m; ++i)
    {
        std::cin >> arr[i];
    }

    int cnt = 0;
    for (int i = 0; i < m; ++i)
    {
        if (mp.find(arr[i]) != mp.end() && mp[arr[i]] == 0)
        {
            ++cnt;
            mp[arr[i]] = 1;
        }
    }

    std::cout << cnt << "\n";
    if (cnt == 0)
    {
        std::cout << 0 << "\n";
        return;
    }

    for (auto &[key, value]: mp)
    {
        value = 0;
    }

    int distinct = 0, len = m;
    for (int l = 0, r = 0; r < m; ++r)
    {
        if (mp.find(arr[r]) != mp.end())
        {
            if (mp[arr[r]]++ == 0)
            {
                ++distinct;
            }
        }

        while (distinct == cnt)
        {
            len = std::min(len, r - l + 1);
            if (mp.find(arr[l]) != mp.end())
            {
                if (--mp[arr[l]] == 0)
                {
                    --distinct;
                }
            }

            ++l;
        }
    }

    std::cout << len << "\n";
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
