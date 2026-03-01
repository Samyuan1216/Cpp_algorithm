#include <bits/stdc++.h>
namespace ranges = std::ranges;

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
T gcd(T a, T b)
{
    return (b == 0? a: gcd(b, a % b));
}

void solve()
{
    constexpr i64 inf = lim<i64>::min();
    i32 n, m, x = 0, y = 0;
    std::cin >> n >> m;

    vi32 v(n + 1), c(n + 1);
    f64 best = 0, ratio;
    for (i32 i = 1; i <= n; i++)
    {
        std::cin >> v[i] >> c[i];

        ratio = (f64)c[i] / v[i];
        if (ratio > best)
        {
            best = ratio;
            x = v[i], y = c[i];
        }
    }

    auto relax_cycle = [&](auto &dist)
    {
        for (i32 i = 1; i <= n; i++)
        {
            if (v[i] != x)
            {
                for (i32 j = 0, d = gcd(v[i], x); j < d; j++)
                {
                    for (i32 cur = j, next, circle = 0; circle < 2; circle += (cur == j)? 1: 0)
                    {
                        next = (cur + v[i]) % x;
                        if (dist[cur] != inf)
                        {
                            dist[next] = std::max(dist[next], dist[cur] - i64((cur + v[i]) / x) * y + c[i]);
                        }
        
                        cur = next;
                    }
                }
            }
        }
    };

    vi64 dp(x, inf);
    dp[0] = 0;
    relax_cycle(dp);

    i64 jobv;
    for (i32 i = 1, v; i <= m; i++)
    {
        std::cin >> jobv;
        
        v = i32(jobv % x);
        if (dp[v] == inf)
        {
            std::cout << -1 << "\n";
        }
        else
        {
            std::cout << jobv / x * y + dp[v] << "\n";
        }
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