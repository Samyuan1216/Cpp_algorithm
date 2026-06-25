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

template<typename T = std::string,
         typename F = decltype([](const std::string &word, int i)
         {
             return word[i] - 'a';
         }),
         int N = 26>
struct AC
{
    std::vector<std::array<int, N>> tree;
    std::vector<int> end;
    std::vector<int> fail;
    std::vector<bool> alert;
    int cnt;
    F compute;

    void build()
    {
        cnt = 0;

        tree.assign(1, std::array<int, N>{});
        fail.assign(1, 0);
        alert.assign(1, false);
    }

    AC(F func = F{}): compute(func)
    {
        build();
    }

    void insert(const T &word)
    {
        int u = 0;
        for (int i = 0, c; i < std::ssize(word); ++i)
        {
            c = compute(word, i);
            if (tree[u][c] == 0)
            {
                if (++cnt >= std::ssize(tree))
                {
                    tree.push_back(std::array<int, N>{});
                    fail.push_back(0);
                    alert.push_back(false);
                }

                tree[u][c] = cnt;
            }

            u = tree[u][c];
        }

        end.push_back(u);
        alert[u] = true;
    }

    void set_fail()
    {
        std::queue<int> q;
        for (int i = 0; i < N; ++i)
        {
            if (tree[0][i] > 0)
            {
                q.push(tree[0][i]);
            }
        }

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int i = 0; i < N; ++i)
            {
                if (tree[u][i] == 0)
                {
                    tree[u][i] = tree[fail[u]][i];
                }
                else
                {
                    fail[tree[u][i]] = tree[fail[u]][i];
                    q.push(tree[u][i]);
                }
            }

            alert[u] = alert[u] || alert[fail[u]];
        }
    }

    std::vector<int> query(std::string &&str)
    {
        std::vector<int> times(cnt);
        for (int i = 0, u = 0; i < std::ssize(str); ++i)
        {
            u = tree[u][compute(str, i)];
            ++times[u];
        }

        std::vector<std::vector<int>> g(cnt);
        for (int i = 0; i < cnt; ++i)
        {
            g[fail[i]].push_back(i);
        }

        auto dfs = [&](auto &&self, int u)
        {
            for (auto &v: g[u])
            {
                self(self, v);
                times[u] += times[v];
            }
        };

        dfs(dfs, 0);

        return times;
    }
};

void solve()
{
    i64 n, k;
    std::cin >> n >> k;

    AC tr;
    for (int i = 0; i < k; ++i)
    {
        std::string str;
        std::cin >> str;

        tr.insert(str);
    }

    tr.set_fail();

    using mint = ModInt<998244353>;
    auto matrix = std::vector(tr.cnt + 1, std::vector<mint>(tr.cnt + 1));

    for (int u = 0; u <= tr.cnt; ++u)
    {
        if (tr.alert[u])
        {
            continue;
        }

        for (int c = 0; c < 26; ++c)
        {
            int v = tr.tree[u][c];
            if (!tr.alert[v])
            {
                matrix[u][v] += 1;
            }
        }
    }

    auto mat_mul = [](auto &&a, auto &&b)
    {
        int n = a.size(), t = a[0].size(), m = b[0].size();
        auto ans = std::vector(n, std::vector<mint>(m));
    
        for (int i = 0; i < n; ++i)
        {
            for (int k = 0; k < t; ++k)
            {
                auto aik =  a[i][k];
                if (aik == 0)
                {
                    continue;
                }

                for (int j = 0; j < m; ++j)
                {
                    ans[i][j] += aik * b[k][j];
                }
            }
        }
    
        return ans;
    };
    
    auto mat_power = [&](auto &&mat, int n)
    {
        int size = mat.size();
        auto ans = std::vector(size, std::vector<mint>(size));
        for (int i = 0; i < size; ++i)
        {
            ans[i][i] = 1;
        }
    
        while (n > 0)
        {
            if (n & 1)
            {
                ans = mat_mul(ans, mat);
            }
    
            mat = mat_mul(mat, mat);
            n >>= 1;
        }
    
        return ans;
    };

    auto matrix_n = mat_power(matrix, n);
    mint ans = 0;

    for (int i = 0; i <= tr.cnt; ++i)
    {
        if (!tr.alert[i])
        {
            ans += matrix_n[0][i];
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
