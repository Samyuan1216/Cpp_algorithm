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

template<int MOD = 998244353>
struct Comb
{
    using mint = ModInt<MOD>;
    std::vector<mint> fac, inv;

    Comb(int n): fac(n + 1), inv(n + 1)
    {
        fac[0] = fac[1] = 1;
        for (int i = 2; i <= n; ++i)
        {
            fac[i] = i * fac[i - 1];
        }

        inv[n] = fac[n].pow(MOD - 2);
        for (int i = n - 1; i >= 0; --i)
        {
            inv[i] = (i + 1) * inv[i + 1];
        }
    }

    mint C(int a, int b)
    {
        if (a < 0 || b < 0 || b > a)
        {
            return 0;
        }

        return fac[a] * inv[b] * inv[a - b];
    }

    mint P(int a, int b)
    {
        if (a < 0 || b < 0 || b > a)
        {
            return 0;
        }

        return fac[a] * inv[a - b];
    };
};

void solve()
{
    constexpr int mod = 998244353;
    using mint = ModInt<mod>;

    int n;
    std::cin >> n;

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    ranges::sort(arr);

    std::vector<mint> suf(n);
    suf[n - 1] = arr[n - 1];

    for (int i = n - 2; i >= 0; --i)
    {
        suf[i] = suf[i + 1] + arr[i];
    }

    Comb comb(n);

    mint ans = 0;
    for (int i = 0, j = n - 1; i < n - 1; ++i, --j)
    {
        ans += comb.fac[n - 1] * comb.fac[j - 1] * comb.inv[j] * (suf[i + 1] - mint(j) * arr[i]);
    }

    std::cout << ans << "\n";
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
