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

void solve()
{
    i64 ts, ta, tb;
    std::cin >> ts >> ta >> tb;

    i128 s = ts, a = ta, b = tb;
    auto exgcd = [&]<typename T>(auto &self, T a, T b) -> std::array<T, 3>
    {
        if (b == 0)
        {
            return {a, 1, 0};
        }
        
        auto [d, x, y] = self(self, b, a % b);
        return {d, y, x - y * (a / b)};
    };

    auto [d, x, y] = exgcd(exgcd, a, b);
    if (s % d != 0)
    {
        std::cout << "No\n";
        return;
    }

    x = x * (s / d), y = y * (s / d);

    i128 p = b / d, q = a / d, t;
    if (x < 0)
    {
        t = (-x + p - 1) / p;
        x += p * t;
        y -= q * t;
    }
    else
    {
        t = x / p;
        x -= p * t;
        y += q * t;
    }

    if (y < 0)
    {
        std::cout << "No\n";
        return;
    }

    i128 ansa = x, ansb = y, limit = std::max(x, y);
    if (x < y)
    {
        i128 k = (y - x) / (p + q);
        for (auto tk: {k, k + 1})
        {
            if (tk < 0 || tk * q > y)
            {
                continue;
            }

            i128 tx = x + tk * p, ty = y - tk * q;
            i128 cur = std::max(tx, ty);
            if (cur < limit)
            {
                limit = cur;
                ansa = tx, ansb = ty;
            }
        }
    }

    std::cout << "Yes\n";
    std::cout << i64(ansa) << " " << i64(ansb) << "\n";
}

i32 main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    i32 t = 1;
    std::cin >> t;
    while (t--)
    {
        solve();
    }
}
