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

template<typename T = int, typename Cmp = std::less<T>>
class Descartes_Tree
{
    Cmp compare;
public:
    const std::vector<T> &arr;
    std::vector<int> left;
    std::vector<int> right;
    std::vector<int> stack;
    int n;
    int root = 0;

    Descartes_Tree(const std::vector<T> &input, int size): arr(input), left(size + 1), right(size + 1), stack(size + 1), n(size)
    {
        for (int i = 1, top = 0, pos = 0; i <= n; ++i)
        {
            pos = top;
            while (pos > 0 && compare(arr[stack[pos]], arr[i]))
            {
                --pos;
            }

            if (pos > 0)
            {
                right[stack[pos]] = i;
            }

            if (pos < top)
            {
                left[i] = stack[pos + 1];
            }

            stack[++pos] = i;
            top = pos;
        }

        if (n > 0)
        {
            root = stack[1];
        }
    }
};

void solve()
{
    constexpr int mod = 1000000007;
    using mint = ModInt<mod>;

    int n, m;
    std::cin >> n >> m;

    auto arr = std::vector<int>(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];
    }

    auto tree = Descartes_Tree(arr, n);

    auto tmp = std::vector<mint>(m + 1);
    auto dp = std::vector(n + 1, std::vector<mint>(m + 1));
    ranges::fill(dp[0], 1);

    auto dfs = [&](auto &&self, int u) -> void
    {
        if (u == 0)
        {
            return;
        }

        self(self, tree.left[u]);
        self(self, tree.right[u]);

        for (int j = 1; j <= m; ++j)
        {
            tmp[j] = dp[tree.left[u]][j - 1] * dp[tree.right[u]][j];
        }

        for (int j = 1; j <= m; ++j)
        {
            dp[u][j] = dp[u][j - 1] + tmp[j];
        }
    };

    dfs(dfs, tree.root);

    std::cout << dp[tree.root][m] << "\n";
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
