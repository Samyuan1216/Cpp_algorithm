// https://www.nowcoder.com/share/jump/1961392931769529836784

#include <bits/stdc++.h>
namespace ranges = std::ranges;
namespace views = std::views;

// 基本类型别名
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128;

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

#ifndef DEBUG
struct __X
{
    __X& operator<<(const auto& str) {return *this;}
    void sp([[maybe_unused]] const string& str = "") {}
} dout;
#define debug(x)
#endif

template<typename T = i32>
class Graph
{
    std::vector<std::vector<T>> matrix;
public:
    Graph(i32 size, T init = T{}): matrix(size + 1, std::vector<T>(size + 1, init)) {};

    std::vector<T>& operator[](i32 idx)
    {
        return matrix[idx];
    }
};

void solve()
{
    i32 n, m;
    std::cin >> n >> m;

    Graph g(n, lim<i32>::max());
    for ([[maybe_unused]] i32 i: views::iota(0, m))
    {
        i32 u, v, w;
        std::cin >> u >> v >> w;

        g[u][v] = std::min(g[u][v], w);
    }

    auto compute = [&](auto a, auto b, auto c)
    {
        return std::min(a, b + c);
    };

    auto floyd = [&](i32 n, auto limit)
    {
        for (i32 k: views::iota(1, n + 1))
        {
            for (i32 i: views::iota(1, n + 1))
            {
                if (g[i][k] == limit)
                {
                    continue;
                }

                for (i32 j: views::iota(1, n + 1))
                {
                    if (g[k][j] == limit)
                    {
                        continue;
                    }

                    g[i][j] = compute(g[i][j], g[i][k], g[k][j]);
                }
            }
        }
    };

    floyd(n, lim<i32>::max());

    i32 ans = 0;
    for (i32 i: views::iota(2, n + 1))
    {
        ans += g[1][i];
        ans += g[i][1];
    }

    std::cout << ans << "\n";
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