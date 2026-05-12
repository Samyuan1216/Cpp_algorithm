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

    int n;
    std::cin >> n;

    std::string s1, s2, s3;
    std::cin >> s1 >> s2 >> s3;

    int len1 = std::ssize(s1), len2 = std::ssize(s2), len3 = std::ssize(s3);
    auto dp = std::vector(n + 1, std::vector(len1, std::vector(len2, std::vector<mint>(len3))));
    dp[0][0][0][0] = 1;

    for (int i = 1; i <= n; ++i)
    {
        for (int l1 = 0; l1 < len1; ++l1)
        {
            for (int l2 = 0; l2 < len2; ++l2)
            {
                for (int l3 = 0; l3 < len3; ++l3)
                {
                    if (dp[i - 1][l1][l2][l3] == 0)
                    {
                        continue;
                    }

                    for (char c = 'a'; c <= 'z'; ++c)
                    {
                        int cl1 = (c == s1[l1]? l1 + 1: l1);
                        int cl2 = (c == s2[l2]? l2 + 1: l2);
                        int cl3 = (c == s3[l3]? l3 + 1: l3);

                        if (cl1 < len1 && cl2 < len2 && cl3 < len3)
                        {
                            dp[i][cl1][cl2][cl3] += dp[i - 1][l1][l2][l3];
                        }
                    }
                }
            }
        }
    }

    mint ans = 0;
    for (int l1 = 0; l1 < len1; ++l1)
    {
        for (int l2 = 0; l2 < len2; ++l2)
        {
            for (int l3 = 0; l3 < len3; ++l3)
            {
                ans += dp[n][l1][l2][l3];
            }
        }
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
