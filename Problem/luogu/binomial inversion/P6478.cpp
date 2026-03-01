#include <bits/stdc++.h>
namespace ranges = std::ranges;
namespace views = std::views;

// 基本类型别名
using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = unsigned __int128;

using f32 = float;
using f64 = double;
using f128 = long double;

// 省略std::
using std::string, std::pair, std::tuple, std::queue, std::stack, std::deque;

// 容器类型 - 一维
using vi32 = std::vector<i32>;
using vu32 = std::vector<u32>;
using vi64 = std::vector<i64>;
using vu64 = std::vector<u64>;
using vf32 = std::vector<f32>;
using vf64 = std::vector<f64>;
using vf128 = std::vector<f128>;
using vb = std::vector<bool>;
using vc = std::vector<char>;
using vs = std::vector<string>;

// 容器类型 - 二维
using v2i32 = std::vector<vi32>;
using v2u32 = std::vector<vu32>;
using v2i64 = std::vector<vi64>;
using v2u64 = std::vector<vu64>;
using v2f32 = std::vector<vf32>;
using v2f64 = std::vector<vf64>;
using v2f128 = std::vector<vf128>;
using v2b = std::vector<vb>;
using v2c = std::vector<vc>;
using v2s = std::vector<vs>;

// 数组类型（固定大小）
template<size_t N>
using ai32 = std::array<i32, N>;
template<size_t N>
using ai64 = std::array<i64, N>;
template<size_t N>
using af32 = std::array<f32, N>;
template<size_t N>
using af64 = std::array<f64, N>;

// 映射类型
template<typename T>
using us = std::unordered_set<T>;
template<typename T1, typename T2>
using um = std::unordered_map<T1, T2>;

// 优先队列
template<typename T, typename F>
using pq = std::priority_queue<T, std::vector<T>, F>;

// 最大最小值
template<typename T>
using lim = std::numeric_limits<T>;

template<typename T>
class Graph
{
    i32 cnt = 1;
public:
    vi32 head, next, to;
    std::vector<T> weight;

    Graph(i32 n, i32 m): head(n + 1), next(m + 1), to(m + 1), weight(m + 1) {}

    void add_edge(i32 u, i32 v, T w = 1)
    {
        next[cnt] = head[u];
        to[cnt] = v;
        weight[cnt] = w;
        head[u] = cnt++;
    }

    struct EdgeIterator
    {
        Graph& g;
        i32 eid;
        
        bool operator!=(i32 end) const {return eid != end;}
        auto operator*() {return std::pair<const i32&, T&>{g.to[eid], g.weight[eid]};}
        void operator++() {eid = g.next[eid];}
    };
    
    struct EdgeRange
    {
        Graph& g;
        i32 u;
        
        EdgeIterator begin() {return {g, g.head[u]};}
        i32 end() {return 0;}
    };
    
    EdgeRange operator[](i32 u) {return {*this, u};}
};

template<typename T>
std::vector<T> get_fact(i32 n, T mod)
{
    std::vector<T> fac(n + 1);

    fac[0] = fac[1] = 1;
    for (i32 i: views::iota(2, n + 1))
    {
        fac[i] = ((i128)i * fac[i - 1]) % mod;
    }

    return std::move(fac);
}

template<typename T>
std::vector<std::vector<T>> C(i32 n, T mod)
{
    std::vector<std::vector<T>> c(n + 1, std::vector<T>(n + 1));
    for (i32 i: views::iota(0, n + 1))
    {
        c[i][0] = 1;
        for (i32 j: views::iota(1, i + 1))
        {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
        }
    }

    return std::move(c);
}

void solve()
{
    constexpr i64 mod = 998244353;
    string str;
    i32 n, m;
    std::cin >> n >> str;

    m = n >> 1;

    vi32 arr(n + 1);
    for (i32 i: views::iota(1, n + 1))
    {
        arr[i] = str[i - 1] - '0';
    }

    Graph<i32> g(n, n << 1);
    for ([[maybe_unused]] i32 i: views::iota(1, n))
    {
        i32 u, v;
        std::cin >> u >> v;

        g.add_edge(u, v);
        g.add_edge(v, u);
    }

    vi32 size(n + 1);
    v2i32 belong(n + 1, vi32(2));
    v2i64 dp(n + 1, vi64(n + 1));
    vi64 backup(n + 1);

    auto dfs = [&](auto &self, auto u, auto f) -> void
    {
        size[u] = 1;
        belong[u][arr[u]] = 1;
        dp[u][0] = 1;

        for (auto [v, w]: g[u])
        {
            if (v != f)
            {
                self(self, v, u);

                for (i32 i: views::iota(0, std::min(size[u] / 2, m) + 1))
                {
                    backup[i] = dp[u][i];
                    dp[u][i] = 0;
                }

                for (i32 l: views::iota(0, std::min(size[u] / 2, m) + 1))
                {
                    for (i32 r: views::iota(0, std::min(size[v] / 2, m - l) + 1))
                    {
                        dp[u][l + r] = (dp[u][l + r] + backup[l] * dp[v][r] % mod) % mod;
                    }
                }

                size[u] += size[v];
                belong[u][0] += belong[v][0];
                belong[u][1] += belong[v][1];
            }
        }

        i32 num = belong[u][arr[u] ^ 1];
        for (i32 i: views::iota(1, std::min(num, m) + 1))
        {
            backup[i] = dp[u][i];
        }

        for (i32 i: views::iota(1, std::min(num, m) + 1))
        {
            dp[u][i] = (dp[u][i] + backup[i - 1] * (num - i + 1) % mod) % mod;
        }
    };

    dfs(dfs, 1, 0);

    auto fac = get_fact(n, mod);
    auto c = C(n, mod);

    vi64 gx(m + 1);
    for (i32 i: views::iota(0, m + 1))
    {
        gx[i] = dp[1][i] * fac[m - i] % mod;
    }

    vi64 f(m + 1);
    for (i32 k: views::iota(0, m + 1))
    {
        for (i32 i: views::iota(k, m + 1))
        {
            if ((i - k) & 1)
            {
                f[k] = (f[k] + c[i][k] * gx[i] % mod * (mod - 1) % mod) % mod;
            }
            else
            {
                f[k] = (f[k] + c[i][k] * gx[i] % mod) % mod;
            }
        }
    }

    for (auto &x: f)
    {
        std::cout << x << "\n";
    }
}

i32 main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    i32 t = 1;
    while (t--)
    {
        solve();
    }
}