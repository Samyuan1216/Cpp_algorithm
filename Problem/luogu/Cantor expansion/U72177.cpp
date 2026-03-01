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

void solve()
{
    i32 n;
    i64 m;
    std::cin >> n >> m;

    vi64 arr(n + 1);
    for (i32 i: views::iota(1, n + 1))
    {
        std::cin >> arr[i];
    }

    vi32 sum(n << 2);
    auto build = [&](auto &self, i32 l, i32 r, i32 i) -> void
    {
        if (l == r)
        {
            sum[i] = 1;
        }
        else
        {
            i32 mid = l + (r - l) / 2;
            self(self, l, mid, i << 1);
            self(self, mid + 1, r, i << 1 | 1);

            sum[i] = sum[i << 1] + sum[i << 1 | 1];
        }
    };

    auto add = [&](auto &self, i32 jobi, i32 jobv, i32 l, i32 r, i32 i) -> void
    {
        if (l == r)
        {
            sum[i] += jobv;
        }
        else
        {
            i32 mid = l + (r - l) / 2;
            if (jobi <= mid)
            {
                self(self, jobi, jobv, l, mid, i << 1);
            }
            else
            {
                self(self, jobi, jobv, mid + 1, r, i << 1 | 1);
            }

            sum[i] = sum[i << 1] + sum[i << 1 | 1];
        }
    };

    auto sumf = [&](auto &self, i32 jobl, i32 jobr, i32 l, i32 r, i32 i) -> i32
    {
        if (l >= jobl && r <= jobr)
        {
            return sum[i];
        }

        i32 mid = l + (r - l) / 2;

        i32 ans = 0;
        if (jobl <= mid)
        {
            ans += self(self, jobl, jobr, l, mid, i << 1);
        }

        if (jobr >= mid + 1)
        {
            ans += self(self, jobl, jobr, mid + 1, r, i << 1 | 1);
        }

        return ans;
    };

    auto get_del = [&](auto &self, i32 k, i32 l, i32 r, i32 i) -> i32
    {
        i32 ans;
        if (l == r)
        {
            sum[i]--;
            ans = l;
        }
        else
        {
            i32 mid = l + (r - l) / 2;
            if (sum[i << 1] >= k)
            {
                ans = self(self, k, l, mid, i << 1);
            }
            else
            {
                ans = self(self, k - sum[i << 1], mid + 1, r, i << 1 | 1);
            }

            sum[i] = sum[i << 1] + sum[i << 1 | 1];
        }

        return ans;
    };

    build(build, 1, n, 1);

    for (i32 i: views::iota(1, n + 1))
    {
        i32 x = arr[i];
        if (x == 1)
        {
            arr[i] = 0;
        }
        else
        {
            arr[i] = sumf(sumf, 1, x - 1, 1, n, 1);
        }

        add(add, x, -1, 1, n, 1);
    }

    arr[n] += m;
    for (i32 i = n; i >= 1; i--)
    {
        arr[i - 1] += arr[i] / (n - i + 1);
        arr[i] %= n - i + 1;
    }

    build(build, 1, n, 1);
    
    for (i32 i: views::iota(1, n + 1))
    {
        arr[i] = get_del(get_del, i32(arr[i] + 1), 1, n, 1);
    }

    for (i32 i: views::iota(1, n + 1))
    {
        std::cout << arr[i] << " \n"[i == n];
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