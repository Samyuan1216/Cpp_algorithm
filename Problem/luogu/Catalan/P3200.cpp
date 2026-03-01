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

vi32 euler(i32 n)
{
    vi32 prime(n / 2 + 1), minpf(n + 1);

    i32 cnt = 0;
    for (i32 i: views::iota(2, n + 1))
    {
        if (minpf[i] == 0)
        {
            prime[cnt++] = i;
        }

        for (i32 j: views::iota(0, cnt))
        {
            if (i * prime[j] > n)
            {
                break;
            }

            minpf[i * prime[j]] = prime[j];
            if (i % prime[j] == 0)
            {
                break;
            }
        }
    }

    return minpf;
}

template<typename T>
T power(T x, i32 n, T mod = lim<T>::max())
{
    T ans = 1;
    while (n > 0)
    {
        if (n & 1)
        {
            ans = ((i128)ans * x) % mod;
        }

        x = ((i128)x * x) % mod;
        n >>= 1;
    }

    return ans;
}

void solve()
{
    i32 n, mod;
    std::cin >> n >> mod;

    auto minpf = euler(2 * n);

    vi32 counts(2 * n + 1);
    ranges::fill(counts.begin() + 2, counts.begin() + n + 1, -1);
    ranges::fill(counts.begin() + n + 2, counts.end(), 1);

    for (i32 i = 2 * n; i >= 2; i--)
    {
        if (minpf[i] != 0)
        {
            counts[minpf[i]] += counts[i];
            counts[i / minpf[i]] += counts[i];
            counts[i] = 0;
        }
    }

    i64 ans = 1;
    for (i32 i: views::iota(2, 2 * n + 1))
    {
        if (counts[i] != 0)
        {
            ans = ans * power(i, counts[i], mod) % mod;
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