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

void solve()
{
    constexpr int mod = 998244353;
    using mint = ModInt<mod>;

    int n, k;
    std::cin >> n >> k;

    std::vector<std::vector<int>> g(n);
    for (int i = 0, u, v; i < n - 1; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    auto power = [&](mint x, int n) -> mint
    {
        mint ans = 1;
        while (n > 0)
        {
            if (n & 1)
            {
                ans = ans * x;
            }

            x *= x;
            n >>= 1;
        }

        return ans;
    };

    auto get_fact = [&](int n) -> std::vector<mint>
    {
        auto fac = std::vector<mint>(n + 1);

        fac[0] = fac[1] = 1;
        for (int i = 2; i <= n; ++i)
        {
            fac[i] = i * fac[i - 1];
        }

        return fac;
    };

    auto fac = get_fact(n);

    auto get_inv = [&](int n) -> std::vector<mint>
    {
        auto inv = std::vector<mint>(n + 1);

        inv[n] = power(fac[n], mod - 2);
        for (int i = n - 1; i >= 0; --i)
        {
            inv[i] = (i + 1) * inv[i + 1];
        }

        return inv;
    };

    auto inv = get_inv(n);

    auto C = [&](int n, int k) -> mint
    {
        return (n < k? 0: fac[n] * inv[k] * inv[n - k]);
    };

    if (k == 1)
    {
        std::cout << n << "\n";
        return;
    }
    else if (k == 2)
    {
        std::cout << C(n, k) << "\n";
        return;
    }

    auto dp = std::vector(n, std::vector<mint>(k + 1));
    mint count = 0;

    [&](this auto &&dfs, int u, int f) -> void
    {
        dp[u][1] = 1;

        std::vector<mint> cnt(k + 1);
        cnt[0] = 1;

        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            dfs(v, u);

            for (int i = 1; i < k; ++i)
            {
                count += dp[v][i] * (cnt[k - i - 1] + cnt[k - i]);
            }

            for (int i = 1; i < k; ++i)
            {
                cnt[i] += dp[v][i];
            }

            for (int i = 1; i <= k; ++i)
            {
                dp[u][i] += dp[v][i - 1] + dp[v][i];
            }
        }
    } (0, 0);

    std::cout << 2 * C(n, k) - count << "\n";
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
