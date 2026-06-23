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
    i64 n;
    std::cin >> n;

    std::vector<std::array<i64, 2>> prime;

    for (i64 i = 2; i * i <= n; ++i)
    {
        while (n > 1 && n % i == 0)
        {
            if (prime.empty() || prime.back()[0] != i)
            {
                prime.push_back({i, 1});
            }
            else
            {
                ++prime.back()[1];
            }

            n /= i;
        }
    }

    if (n > 1)
    {
        prime.push_back({n, 1});
    }

    std::vector<i64> fact;
    [&](this auto &&dfs, int index, i64 res) -> void
    {
        if (index == std::ssize(prime))
        {
            fact.push_back(res);
            return;
        }

        i64 p = 1;
        for (int i = 0; i <= prime[index][1]; ++i)
        {
            dfs(index + 1, res * p);
            if (i < prime[index][1])
            {
                p *= prime[index][0];
            }
        }
    } (0, 1);

    int k = std::ssize(fact);
    ranges::sort(fact);

    auto div = std::vector(k, std::vector<int>(k, -1));
    for (int i = 0; i < k; ++i)
    {
        for (int a = 0; a < k; ++a)
        {
            if (fact[i] % fact[a] != 0)
            {
                continue;
            }

            auto it = ranges::lower_bound(fact, fact[i] / fact[a]);
            if (it != fact.end() && *it == fact[i] / fact[a])
            {
                div[a][i] = std::distance(fact.begin(), it);
            }
        }
    }

    using mint = ModInt<998244353>;
    auto dp0 = std::vector(15, std::vector<mint>(k));
    auto dp1 = std::vector(15, std::vector<mint>(k));
    dp0[0][0] = 1;

    for (int a = 0; a < k; ++a)
    {
        for (int i = k - 1; i >= 0; --i)
        {
            int j = div[a][i];
            if (j == -1)
            {
                continue;
            }

            for (int b = 14; b >= 1; --b)
            {
                dp1[b][i] += dp1[b - 1][j] + dp0[b - 1][j] * fact[a];
                dp0[b][i] += dp0[b - 1][j];
            }
        }
    }

    mint ans = 0, f = 1;
    for (int b = 1; b <= 14; ++b)
    {
        f *= b;
        ans += dp1[b][k - 1] * f;
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
