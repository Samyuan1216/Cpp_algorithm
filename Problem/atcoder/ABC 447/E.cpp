#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = int64_t;

template<typename T>
using lim = std::numeric_limits<T>;

#ifndef YUAN_DEBUG
struct __X
{
    __X& operator<<(const auto& str) {return *this;}
    void sp([[maybe_unused]] const std::string& str = "") {}
} dout;
#define debug(x)
#endif

template <i64 MOD>
class ModInt
{
    i64 val;

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
public:
    ModInt(i64 v = 0)
    {
        if (v < 0)
        {
            v = v % MOD + MOD;
        }

        val = v % MOD;
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
        val = val * other.val % MOD;

        return *this;
    }

    ModInt& operator/=(const ModInt& other)
    {
        return *this *= other.inv();
    }


    ModInt operator-() const
    {
        return ModInt(-val);
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
        ModInt temp = *this; *this -= 1; return temp;
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

class DSU
{
    std::vector<int> father, size;
public:
    DSU(int n): father(n + 1), size(n + 1, 1)
    {
        for (int i = 1; i <= n; ++i)
        {
            father[i] = i;
        }
    }

    int find(int i)
    {
        if (i != father[i])
        {
            father[i] = find(father[i]);
        }

        return father[i];
    }

    void merge(int x, int y)
    {
        int fx = find(x), fy = find(y);
        if (fx == fy)
        {
            return;
        }

        if (size[fx] < size[fy])
        {
            std::swap(fx, fy);
        }

        father[fy] = fx;
        size[fx] += size[fy];
    }

    int get_size(int i)
    {
        return size[find(i)];
    }

    bool same(int x, int y)
    {
        return find(x) == find(y);
    }
};

void solve()
{
    constexpr i64 mod = 998244353;
    using mint = ModInt<mod>;

    int n, m;
    std::cin >> n >> m;

    auto edges = std::vector(m + 1, std::array<int, 2>());
    auto costs = std::vector<mint>(m + 1);
    costs[0] = 1;

    for (int i = 1; i <= m; ++i)
    {
        std::cin >> edges[i][0] >> edges[i][1];

        costs[i] = costs[i - 1] * 2;
    }

    DSU uf(n + 1);
    mint ans = 0;
    int cnt = n;

    for (int i = m; i > 0; --i)
    {
        if (!uf.same(edges[i][0], edges[i][1]))
        {
            if (cnt > 2)
            {
                uf.merge(edges[i][0], edges[i][1]);
                --cnt;
            }
            else
            {
                ans += costs[i];
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
