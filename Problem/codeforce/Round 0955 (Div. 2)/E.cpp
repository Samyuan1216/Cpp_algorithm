#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;
using u64 = unsigned long long;

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
    using mint = ModInt<1000000007>;

    struct Data
    {
        i64 l = 0, r = 0;
        mint ans = 0;
    };

    auto merge = [&](Data a, i64 len1, Data b, i64 len2) -> Data
    {
        return {a.l + (a.l == len1? b.l: 0), b.r + (b.r == len2? a.r: 0), a.ans + b.ans + mint(a.r) * b.l};
    };

    [[maybe_unused]] static auto dp = [&]() -> std::array<std::array<Data, 62>, 62>
    {
        std::array<std::array<Data, 62>, 62> dp = {};
        for (int k = 0; k <= 60; ++k)
        {
            dp[0][k + 1] = {1, 1, 1};
        }

        for (int m = 1; m <= 60; ++m)
        {
            for (int k = -1; k <= 60; ++k)
            {
                dp[m][k + 1] = merge(dp[m - 1][k + 1], 1ll << (m - 1), (k >= 0? dp[m - 1][k]: Data()), 1ll << (m - 1));
            }
        }

        return dp;
    } ();

    auto f = [&](this auto &self, i64 n, int k) -> Data
    {
        if (n == 0 || k < 0)
        {
            return Data();
        }

        int m = std::bit_width(u64(n)) - 1;
        if (std::popcount(u64(n)) == 1)
        {
            return dp[m][k + 1];
        }

        i64 len = 1ll << m;
        return merge(dp[m][k + 1], len, self(n - len, k - 1), n - len);
    };

    i64 n, k;
    std::cin >> n >> k;
    std::cout << f(n, k).ans << "\n";
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
