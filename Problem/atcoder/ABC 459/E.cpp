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

template <int MOD>
struct ModInt
{
    int val;

    ModInt(i64 v = 0)
    {
        v %= MOD;
        if (v < 0)
        {
            v += MOD;
        }
        val = static_cast<int>(v);
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
        return pow(MOD - 2);
    }

    ModInt& operator+=(const ModInt& other)
    {
        val += other.val;
        if (val >= MOD)
        {
            val -= MOD;
        }
        return *this;
    }

    ModInt& operator-=(const ModInt& other)
    {
        val -= other.val;
        if (val < 0)
        {
            val += MOD;
        }
        return *this;
    }

    ModInt& operator*=(const ModInt& other)
    {
        val = static_cast<int>(1LL * val * other.val % MOD);
        return *this;
    }

    ModInt& operator/=(const ModInt& other)
    {
        return *this *= other.inv();
    }

    ModInt operator-() const
    {
        return ModInt(val == 0 ? 0 : MOD - val);
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
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> g(n);
    for (int i = 1, p; i < n; ++i)
    {
        std::cin >> p;
        --p;

        g[p].push_back(i);
    }

    constexpr int mod = 998244353;
    using mint = ModInt<mod>;

    std::vector<mint> c(n);
    for (auto &x: c)
    {
        std::cin >> x;
    }

    std::vector<mint> d(n);
    for (auto &x: d)
    {
        std::cin >> x;
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
    
    auto fac = [&](int n) -> std::vector<mint>
    {
        auto fac = std::vector<mint>(n + 1);
    
        fac[0] = fac[1] = 1;
        for (int i = 2; i <= n; ++i)
        {
            fac[i] = i * fac[i - 1];
        }
    
        return fac;
    } ((*ranges::max_element(d)).val);
    
    auto inv = [&](int n) -> std::vector<mint>
    {
        auto inv = std::vector<mint>(n + 1);
    
        inv[n] = power(fac[n], mod - 2);
        for (int i = n - 1; i >= 0; --i)
        {
            inv[i] = (i + 1) * inv[i + 1];
        }
    
        return inv;
    } ((*ranges::max_element(d)).val);

    auto C = [&](mint n, mint r) -> mint
    {
        if (n < r || r < 0)
        {
            return 0;
        }

        if (r == 0)
        {
            return 1;
        }

        mint num = 1;
        for (mint i = 0; i < r; ++i)
        {
            num *= n - i;
        }

        return num * inv[r.val];
    };

    mint ans = 1;
    [&](this auto &&dfs, int u) -> mint
    {
        mint cur = c[u];
        for (auto &v: g[u])
        {
            cur += dfs(v);
        }

        if (cur < d[u])
        {
            ans = 0;

            return 0;
        }

        ans *= C(cur, d[u]);
        return cur - d[u];
    } (0);

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
