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

template <int MOD_ID>
class ModInt
{
    int val;
    inline static int dynamic_mod = 998244353;
public:
    ModInt(i64 v = 0)
    {
        int mod = get_mod();
        v %= mod;

        if (v < 0)
        {
            v += mod;
        }

        val = static_cast<int>(v);
    }

    static int get_mod()
    {
        if constexpr (MOD_ID > 0)
        {
            return MOD_ID;
        }
        else
        {
            return dynamic_mod;
        }
    }

    static void set_mod(int m)
    {
        if constexpr (MOD_ID <= 0)
        {
            dynamic_mod = m;
        }
    }

    ModInt pow(i64 p) const
    {
        ModInt res = 1, a = *this;
        while (p > 0)
        {
            if (p & 1)
            {
                res *= a;
            }
            a *= a;
            p >>= 1;
        }

        return res;
    }

    ModInt inv() const
    {
        auto exgcd = [&](auto &&self, int a, int b) -> std::array<int, 3>
        {
            if (b == 0)
            {
                return {a, 1, 0};
            }
            
            auto [d, x, y] = self(self, b, a % b);
            return {d, y, x - y * (a / b)};
        };

        auto [d, x, y] = exgcd(exgcd, val, get_mod());
        
        return ModInt(x);
    }

    ModInt& operator+=(const ModInt& other)
    {
        val += other.val;
        if (val >= get_mod())
        {
            val -= get_mod();
        }

        return *this;
    }

    ModInt& operator-=(const ModInt& other)
    {
        val -= other.val;
        if (val < 0)
        {
            val += get_mod();
        }

        return *this;
    }

    ModInt& operator*=(const ModInt& other)
    {
        val = static_cast<int>(1LL * val * other.val % get_mod());
        return *this;
    }

    ModInt& operator/=(const ModInt& other)
    {
        return *this *= other.inv();
    }

    ModInt operator-() const
    {
        return ModInt(val == 0 ? 0 : get_mod() - val);
    }

    ModInt& operator++()
    {
        return *this += 1;
    }

    ModInt& operator--()
    {
        return *this -= 1;
    }

    ModInt operator++(int)
    {
        ModInt temp = *this;
        *this += 1;

        return temp;
    }

    ModInt operator--(int)
    {
        ModInt temp = *this; 
        *this -= 1; 

        return temp;
    }

    friend ModInt operator+(ModInt a, const ModInt& b)
    {
        return a += b;
    }

    friend ModInt operator-(ModInt a, const ModInt& b)
    {
        return a -= b;
    }

    friend ModInt operator*(ModInt a, const ModInt& b)
    {
        return a *= b;
    }

    friend ModInt operator/(ModInt a, const ModInt& b)
    {
        return a /= b;
    }

    auto operator<=>(const ModInt& other) const = default;

    friend std::istream& operator>>(std::istream& is, ModInt& m)
    {
        i64 v;
        is >> v;

        m = ModInt(v);
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const ModInt& m)
    {
        return os << m.val;
    }
};

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
    constexpr int mod = 998244353;
    using mint = ModInt<mod>;

    int n, m;
    std::cin >> n >> m;

    std::string str;
    std::cin >> str;

    auto next_array = [&](std::string &str) -> std::vector<int>
    {
        int n = str.length();
        if (n == 1)
        {
            return std::vector<int>{-1};
        }
    
        auto next = std::vector<int>(n);
        next[0] = -1;
    
        int i = 2, m = 0;
        while (i < n)
        {
            if (str[i - 1] == str[m])
            {
                next[i++] = ++m;
            }
            else if (m > 0)
            {
                m = next[m];
            }
            else
            {
                next[i++] = 0;
            }
        }
    
        return next;
    };

    auto next = next_array(str);

    std::vector<std::array<mint, 4>> p(n);
    for (auto &[a, t, g, c]: p)
    {
        std::cin >> a >> t >> g >> c;
    }

    __gnu_pbds::gp_hash_table<char, int, custom_hash> trans;
    trans['A'] = 0, trans['T'] = 1, trans['G'] = 2, trans['C'] = 3;

    std::vector<std::array<int, 4>> to(m);
    for (int i = 0; i < m; ++i)
    {
        for (int c = 0; c < 4; ++c)
        {
            if (trans[str[i]] == c)
            {
                to[i][c] = i + 1;
            }
            else
            {
                int k = next[i];
                while (k != -1 && trans[str[k]] != c)
                {
                    k = next[k];
                }

                to[i][c] = k + 1;
            }
        }
    }

    auto dp = std::vector(n + 1, std::vector(m + 1, std::array<mint, 2>()));
    dp[0][0][0] = 1;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j <= m; ++j)
        {
            for (int c = 0; c < 4; ++c)
            {
                if (p[i][c] == 0)
                {
                    continue;
                }

                int nextj = (j == m? m: to[j][c]);
                if (j < m && dp[i][j][0] != 0)
                {
                    dp[i + 1][nextj][(nextj == m? 1: 0)] += dp[i][j][0] * p[i][c];
                }

                if (dp[i][j][1] != 0)
                {
                    dp[i + 1][nextj][1] += dp[i][j][1] * p[i][c];
                }
            }
        }
    }

    mint ans = 0;
    for (int i = 0; i <= m; ++i)
    {
        ans += dp[n][i][1];
    }

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
