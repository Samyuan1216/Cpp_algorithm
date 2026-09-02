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

    int n, m, maxv;
    std::cin >> n >> m >> maxv;

    std::vector<int> w(n);
    for (auto &x: w)
    {
        std::cin >> x;
    }

    std::vector<int> head(n, -1), next(m << 1), to(m << 1);
    int cntg = 0;

    auto add_edge = [&](int u, int v) -> void
    {
        next[cntg] = head[u];
        to[cntg] = v;
        head[u] = cntg++;
    };

    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        add_edge(u, v);
        add_edge(v, u);
    }

    std::vector<int> dfn(n, -1), low(n), belong(n);
    std::stack<int> sta;
    int cntd = 0, ebcc = 0;

    [&](this auto &&self, int u, int pre) -> void
    {
        dfn[u] = low[u] = cntd++;
        sta.push(u);

        for (int ei = head[u], v; ei != -1; ei = next[ei])
        {
            if ((ei ^ 1) == pre)
            {
                continue;
            }

            v = to[ei];
            if (dfn[v] == -1)
            {
                self(v, ei);

                low[u] = std::min(low[u], low[v]);
            }
            else
            {
                low[u] = std::min(low[u], dfn[v]);
            }
        }

        if (int t; dfn[u] == low[u])
        {
            do
            {
                t = sta.top();
                sta.pop();

                belong[t] = ebcc;
            } while (t != u);

            ++ebcc;
        }
    } (0, -1);

    std::vector<int> color(n);
    std::vector<bool> visit(ebcc);

    mint ans = 1;
    for (int i = 0; i < n; ++i)
    {
        if (visit[belong[i]])
        {
            continue;
        }

        visit[belong[i]] = true;

        int num = -1;
        bool s1 = true, s2 = true;

        [&](this auto &&self, int u, int c) -> void
        {
            color[u] = c;
            if (w[u] >= 0)
            {
                if (num == -1)
                {
                    num = w[u];
                }
                else if (w[u] != num)
                {
                    s1 = false;
                }
            }

            for (int ei = head[u], v; ei != -1; ei = next[ei])
            {
                v = to[ei];
                if (belong[v] != belong[i])
                {
                    continue;
                }

                if (color[v] == 0)
                {
                    self(v, -c);
                }
                else if (color[u] == color[v])
                {
                    s2 = false;
                }
            }
        } (i, 1);

        if (!s1)
        {
            std::cout << 0 << "\n";
            return;
        }

        if (!s2 && num > 0)
        {
            std::cout << 0 << "\n";
            return;
        }

        ans *= (s2 && num == -1? maxv: 1);
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
