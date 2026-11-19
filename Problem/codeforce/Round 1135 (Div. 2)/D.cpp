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

    // 注意：当 p < n 时，构建的时候必须是 Comb<mod> comb(mod - 1); 预处理的值不能比 mod 大
    mint lucas(int a, int b)
    {
        if (b == 0)
        {
            return 1;
        }

        return lucas(a / MOD, b / MOD) * C(a % MOD, b % MOD);
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

constexpr int mod = 1000000007;
using mint = ModInt<mod>;

Comb<mod> comb(2e5 + 10);

void solve()
{
    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    std::vector<i64> pre(n);
    pre[0] = arr[0];

    for (int i = 1; i < n; ++i)
    {
        pre[i] = pre[i - 1] + arr[i];
    }

    ranges::reverse(arr);

    std::vector<i64> suf(n);
    suf[0] = arr[0];

    for (int i = 1; i < n; ++i)
    {
        suf[i] = suf[i - 1] + arr[i];
    }

    std::map<i64, std::vector<int>> mp;
    for (int i = 0; i < n - 1; ++i)
    {
        mp[pre[i] - suf[i]].push_back(i + 1);
    }

    auto compute = [&](int i, int v) -> int
    {
        if ((n & 1) && i == n / 2 + 1)
        {
            return std::ssize(mp[0]);
        }

        int l = std::min(i, n - i + 1), r = std::max(i - 1, n - i);
        int neg = (i <= n / 2? -1: 1);

        int cnt1 = 0;
        if (std::ssize(mp[0]) > 0)
        {
            int idx = std::distance(mp[0].begin(), ranges::lower_bound(mp[0], l));
            if (idx > 0)
            {
                cnt1 += idx;
            }
        }

        int cnt2 = 0;
        if (std::ssize(mp[0]) > 0)
        {
            int idx = std::distance(ranges::upper_bound(mp[0], r), mp[0].end());
            if (idx < std::ssize(mp[0]))
            {
                cnt2 += idx;
            }
        }

        int cnt3 = 0;
        if (std::ssize(mp[neg * v]) > 0)
        {
            int il = std::distance(mp[neg * v].begin(), ranges::lower_bound(mp[neg * v], l));
            int ir = std::distance(mp[neg * v].begin(), ranges::upper_bound(mp[neg * v], r)) - 1;
            if (il <= ir)
            {
                cnt3 += std::max(0, ir - il + 1);
            }
        }

        return cnt1 + cnt2 + cnt3;
    };

    while (q--)
    {
        int i, v;
        std::cin >> i >> v;
        std::cout << comb.C(compute(i, v), m - 1) << "\n";
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