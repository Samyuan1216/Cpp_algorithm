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

constexpr int mod = 998244353;
using mint = ModInt<mod>;

void solve()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::array<int, 2>>> g(n);
    for (int i = 0, u, v, w; i < m; ++i)
    {
        std::cin >> u >> v >> w;
        --u, --v;

        g[u].push_back({v, w});
    }

    auto dijkstra = [&]() -> std::vector<mint>
    {
        struct Cmp
        {
            bool operator()(const std::tuple<int, int, int, mint>& a, const std::tuple<int, int, int, mint>& b) const
            {
                return std::tie(std::get<0>(a), std::get<1>(a)) > std::tie(std::get<0>(b), std::get<1>(b));
            }
        };

        std::priority_queue<std::tuple<int, int, int, mint>, std::vector<std::tuple<int, int, int, mint>>, Cmp> heap;
        heap.push({0, 0, 0, 0});

        std::vector<mint> dist(n);
        std::vector<bool> vis(n);

        int rank = 0;
        std::array<int, 2> last{};

        while (!heap.empty())
        {
            auto [r, c, u, x] = heap.top();
            heap.pop();

            if (vis[u])
            {
                continue;
            }

            vis[u] = true;
            if (last != std::array{r, c})
            {
                ++rank;
                last = std::array{r, c};
            }

            dist[u] = x;
            for (auto &[v, w]: g[u])
            {
                if (!vis[v])
                {
                    heap.push({rank, w, v, x * 10 + w});
                }
            }
        }

        return dist;
    };

    auto dist = dijkstra();
    for (int i = 1; i < n; ++i)
    {
        std::cout << dist[i] << "\n";
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    // std::cin >> t;
    while (t--)
    {
        solve();
    }
}