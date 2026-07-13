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
    using mint = ModInt<1000000007>;

    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    std::vector<int> u{-1}, cnt{0};
    int k = 0;

    for (int i = 0; i < n; ++i)
    {
        if (u.back() != arr[i])
        {
            if (u.back() + 1 == arr[i])
            {
                ++k;
            }

            u.push_back(arr[i]);
            cnt.push_back(0);
        }

        ++cnt.back();
    }

    mint ans = 1;
    for (int i = 1; i < std::ssize(u); ++i)
    {
        ans *= mint(2).pow(cnt[i] - 1);
    }

    if (cnt[0] > 0)
    {
        ans *= mint(2).pow(cnt[0] - 1) * (k + 1);
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
