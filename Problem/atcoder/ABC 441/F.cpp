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
    i32 n, m;
    std::cin >> n >> m;

    vi32 p(n);
    vi64 v(n);
    for (i32 i: views::iota(0, n))
    {
        std::cin >> p[i] >> v[i];
    }

    v2i64 dp(n + 1, vi64(m + 1));
    for (i32 i: views::iota(1, n + 1))
    {
        for (i32 j: views::iota(0, m + 1))
        {
            if (j < p[i - 1])
            {
                dp[i][j] = dp[i - 1][j];
            }
            else
            {
                dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - p[i - 1]] + v[i - 1]);
            }
        }
    }

    v2i64 dp2(n + 1, vi64(m + 1));
    for (i32 i = n - 1; i >= 0; i--)
    {
        for (i32 j = 0; j <= m; j++)
        {
            if (j < p[i])
            {
                dp2[i][j] = dp2[i + 1][j];
            }
            else
            {
                dp2[i][j] = std::max(dp2[i + 1][j], dp2[i + 1][j - p[i]] + v[i]);
            }
        }
    }

    string ans;
    i64 target = dp[n][m];
    for (i32 i: views::iota(0, n))
    {
        i64 max_without_i = 0;
        for (i32 j: views::iota(0, m + 1))
        {
            max_without_i = std::max(max_without_i, dp[i][j] + dp2[i + 1][m - j]);
        }

        i64 max_with_i = 0;
        for (i32 j: views::iota(0, m - p[i] + 1))
        {
            max_with_i = std::max(max_with_i, dp[i][j] + dp2[i + 1][m - p[i] - j]);
        }

        if (max_without_i < target)
        {
            ans += 'A';
        }
        else if (max_with_i < target - v[i])
        {
            ans += 'C';
        }
        else
        {
            ans += 'B';
        }
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
