#include <bits/extc++.h>
namespace ranges = std::ranges;
namespace pbds = __gnu_pbds;

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

void solve()
{
    i64 n;
    std::string str;
    std::cin >> n >> str;

    auto count = [&](char a, char b) -> i64
    {
        pbds::gp_hash_table<int, i64, custom_hash> cnt;
        cnt[0] = 1;

        int diff = 0;
        i64 res = 0;

        for (auto &c: str)
        {
            if (c == a)
            {
                ++diff;
            }
            else if (c == b)
            {
                --diff;
            }

            res += cnt[diff];
            ++cnt[diff];
        }

        return res;
    };

    auto count_all = [&]() -> i64
    {
        pbds::gp_hash_table<std::pair<int, int>, i64, custom_hash> cnt;
        cnt[{0, 0}] = 1;

        int A = 0, B = 0, C = 0;
        i64 res = 0;

        for (auto &c: str)
        {
            if (c == 'A')
            {
                ++A;
            }
            else if (c == 'B')
            {
                ++B;
            }
            else
            {
                ++C;
            }

            res += cnt[{A - B, A - C}];
            ++cnt[{A - B, A - C}];
        }

        return res;
    };

    std::cout << n * (n + 1) / 2 - count('A', 'B') - count('A', 'C') - count('B', 'C') + 2 * count_all() << "\n";
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
