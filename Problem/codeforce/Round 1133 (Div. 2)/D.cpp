#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

#ifndef YUAN_DEBUG
struct __X
{
    __X& operator<<(const auto& str) {return *this;}
    void sp([[maybe_unused]] const std::string& str = "") {}
} dout;
#define debug(x)
#endif

template<int MOD>
struct ModInt
{
    i64 x;

    ModInt(i64 v = 0): x((v % MOD + MOD) % MOD) {}

    ModInt pow(i64 n) const
    {
        ModInt a = *this, r = 1;
        for (; n; n >>= 1, a *= a)
            if (n & 1) r *= a;
        return r;
    }

    ModInt inv() const { return pow(MOD - 2); }

    ModInt& operator+=(const ModInt& b)
    {
        if ((x += b.x) >= MOD) x -= MOD;
        return *this;
    }

    ModInt& operator-=(const ModInt& b)
    {
        if ((x -= b.x) < 0) x += MOD;
        return *this;
    }

    ModInt& operator*=(const ModInt& b)
    {
        x = 1LL * x * b.x % MOD;
        return *this;
    }

    ModInt& operator/=(const ModInt& b)
    {
        return *this *= b.inv();
    }

    friend ModInt operator+(ModInt a, const ModInt& b) { return a += b; }
    friend ModInt operator-(ModInt a, const ModInt& b) { return a -= b; }
    friend ModInt operator*(ModInt a, const ModInt& b) { return a *= b; }
    friend ModInt operator/(ModInt a, const ModInt& b) { return a /= b; }

    friend std::istream& operator>>(std::istream& in, ModInt& a)
    {
        i64 v;
        return in >> v, a = v, in;
    }
    friend std::ostream& operator<<(std::ostream& out, const ModInt& a)
    {
        return out << a.x;
    }
};

using mint = ModInt<998244353>;

void solve()
{
    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }
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