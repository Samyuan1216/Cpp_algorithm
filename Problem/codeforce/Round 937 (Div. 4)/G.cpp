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
    i32 n;
    std::cin >> n;

    vi32 g(n), w(n);
    um<string, i32> idx;
    i32 cnt = 0;
    
    auto get_idx = [&](string &str)
    {
        if (!idx.contains(str))
        {
            idx[str] = ++cnt;
        }

        return idx[str];
    };

    for (i32 i: views::iota(0, n))
    {
        string str1, str2;
        std::cin >> str1 >> str2;

        g[i] = get_idx(str1), w[i] = get_idx(str2);
    }

    v2i32 dp(1 << (n + 1), vi32(n + 1, -1));
    auto dfs = [&](auto &self, i32 status, i32 i) -> i32
    {
        if (i != -1 && dp[status][i] != -1)
        {
            return dp[status][i];
        }

        i32 ans = 0;
        for (i32 j: views::iota(0, n))
        {
            if (status & (1 << j))
            {
                continue;
            }

            if (i != -1 && g[i] != g[j] && w[i] != w[j])
            {
                continue;
            }

            ans = std::max(ans, self(self, status | (1 << j), j) + 1);
        }

        if (i != -1)
        {
            dp[status][i] = ans;
        }

        return ans;
    };

    std::cout << n - dfs(dfs, 0, -1) << "\n";
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