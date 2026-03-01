#include <bits/stdc++.h>
#include <bits/extc++.h>
namespace ranges = std::ranges;
namespace views = std::views;

using i64 = int64_t;
using i128 = __int128;
using u64 = uint64_t;
using u128 = unsigned __int128;
using f64 = double;
using f128 = long double;

template<typename T>
using lim = std::numeric_limits<T>;

#ifndef DEBUG
struct __X
{
    __X& operator<<(const auto& str) {return *this;}
    void sp([[maybe_unused]] const std::string& str = "") {}
} dout;
#define debug(x)
#endif

class custom_hash
{
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
    auto euler = [&](int n)
    {
        std::vector<bool> visited(n + 1);
        std::vector<int> prime(n / 2 + 1);

        std::vector<int> min_prime(n + 1);
        min_prime[1] = 1;
    
        int cnt = 0;
        for (int i = 2; i <= n; ++i)
        {
            if (!visited[i])
            {
                prime[cnt++] = i;
                min_prime[i] = i;
            }
    
            for (int j = 0; j < cnt; ++j)
            {
                if (i * prime[j] > n)
                {
                    break;
                }
    
                visited[i * prime[j]] = true;
                min_prime[i * prime[j]] = prime[j];
                if (i % prime[j] == 0)
                {
                    break;
                }
            }
        }
    
        return min_prime;
    };

    static std::vector<int> min_prime;
    static bool compute = false;
    if (!compute)
    {
        min_prime = euler(10000010);
        compute = true;
    }

    constexpr i64 mod = 998244353;
    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    std::vector<hash_table<int, int>> count(n);
    for (int i = 0, x; i < n; ++i)
    {
        x = arr[i];
        while (x > 1)
        {
            count[i][min_prime[x]]++;
            x /= min_prime[x];
        }
    }

    hash_table<int, int> e1, e2;
    for (auto &map: count)
    {
        for (auto [key, cnt]: map)
        {
            if (cnt > e1[key])
            {
                e2[key] = e1[key];
                e1[key] = cnt;
            }
            else if (cnt > e2[key])
            {
                e2[key] = cnt;
            }
        }
    }

    auto power = [&]<typename T>(T x, int n, T mod = lim<T>::max())
    {
        T ans = 1;
        while (n > 0)
        {
            if (n & 1)
            {
                ans = ((i128)ans * x) % mod;
            }
    
            x = ((i128)x * x) % mod;
            n >>= 1;
        }
    
        return ans;
    };

    i64 lcm = 1;
    for (auto [key, cnt]: e1)
    {
        lcm = (lcm * power(i64(key), cnt, mod)) % mod;
    }

    std::vector<i64> ans(n, lcm);
    for (int i = 0; i < n; ++i)
    {
        for (auto [key, cnt]: count[i])
        {
            if (cnt == e1[key])
            {
                ans[i] = ((ans[i] * power(power(i64(key), cnt, mod), mod - 2, mod)) % mod * power(i64(key), e2[key], mod)) % mod;
            }
        }
    }

    for (int i = 0; i < n; ++i)
    {
        std::cout << ans[i] << " \n"[i == n - 1];
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    std::cin >> t;
    while (t--)
    {
        solve();
    }
}
