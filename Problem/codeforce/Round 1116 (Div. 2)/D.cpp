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
    constexpr int mod = 998244353;
    using mint = ModInt<mod>;

    int n;
    std::string str;
    std::cin >> n >> str;

    int cnt0 = 0, seg0 = 0, cnt1 = 0, seg1 = 0;
    for (int i = 0; i < n; ++i)
    {
        if (i == 0 || str[i] != str[i - 1])
        {
            (str[i] == '0'? ++seg0: ++seg1);
        }

        (str[i] == '0'? ++cnt0: ++cnt1);
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

    auto fac = get_fact(std::max(cnt0, cnt1));
    
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

    auto inv = get_inv(std::max(cnt0, cnt1));
    
    auto C = [&](int n, int k) -> mint
    {
        if (k < 0 || k > n || n < 0)
        {
            return 0;
        }

        return fac[n] * inv[k] * inv[n - k];
    };

    mint ans0 = (cnt0 == 0 ? 1 : C(cnt0 - 1, seg0 - 1));
    mint ans1 = (cnt1 == 0 ? 1 : C(cnt1 - 1, seg1 - 1));
    std::cout << ans0 * ans1 << "\n";
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
