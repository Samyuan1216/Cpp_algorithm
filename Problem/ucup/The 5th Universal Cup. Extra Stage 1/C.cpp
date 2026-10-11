#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

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

constexpr int C[3][3] =
{
    {1, 0, 0},
    {1, 1, 0},
    {1, 2, 1}
};

int lucas(u64 n, u64 k)
{
    if (k > n) return 0;

    int ans = 1;
    while (n > 0 || k > 0)
    {
        int ni = n % 3;
        int ki = k % 3;

        if (ki > ni) return 0;

        ans = ans * C[ni][ki] % 3;
        n /= 3;
        k /= 3;
    }

    return ans;
}

void solve()
{
    constexpr int mod = 3;
    using mint = ModInt<mod>;

    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    mint ans = 0;
    for (int i = 0; i < n; ++i)
    {
        ans += lucas(n - 1, i) * arr[i];
    }

    if ((n - 1) & 1)
    {
        ans = mint(0) - ans;
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
