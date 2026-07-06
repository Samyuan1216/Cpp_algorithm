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
    using mint = ModInt<998244353>;

    std::string high;
    std::cin >> high;

    int n = std::ssize(high);
    std::string low = std::string(n - 1, '0') + "1";

    auto flat_index = [](auto ...D)
    {
        return [=](auto ...i)
        {
            int idx = 0;
            ((idx = idx * D + i), ...);
    
            return idx;
        };
    };
    auto idx = flat_index(n, 2, 2, 2, 3, 1024);
    
    std::vector<int> dp(n * 2 * 2 * 2 * 3 * 1024, -1);
    auto digit_dp = [&](this auto &&digit_dp, int i, bool limit_low, bool limit_high, bool is_num, int rem3, int mask) -> mint
    {
        if (i == n)
        {
            if (!is_num)
            {
                return 0;
            }

            int c1 = (rem3 == 0), c2 = ((mask >> 3) & 1), c3 = (std::popcount(unsigned(mask)) == 3);
            return (c1 + c2 + c3 == 1? 1: 0);
        }
    
        if (dp[idx(i, limit_low, limit_high, is_num, rem3, mask)] != -1)
        {
            return dp[idx(i, limit_low, limit_high, is_num, rem3, mask)];
        }
    
        mint ans = 0;
        if (!is_num && low[i] == '0')
        {
            ans += digit_dp(i + 1, true, false, false, 0, 0);
        }
    
        int lo = (limit_low? (low[i] - '0'): 0), hi = (limit_high? (high[i] - '0'): 9), d0 = (is_num? 0: 1);
        for (int d = std::max(lo, d0); d <= hi; ++d)
        {
            int nr = (rem3 * 10 + d) % 3, nm = mask | (1 << d);
            ans += digit_dp(i + 1, limit_low && d == lo, limit_high && d == hi, true, nr, nm);
        }
    
        dp[idx(i, limit_low, limit_high, is_num, rem3, mask)] = ans.val;
        return ans;
    };

    std::cout << digit_dp(0, true, true, false, 0, 0) << "\n";
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
