#include <bits/stdc++.h>

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
using std::string, std::pair, std::tuple;

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

constexpr int MAXN = 15;
vi64 m(MAXN), r(MAXN);
i32 t, k;

template<typename T>
class exgcd
{
public:
    inline static T d, x, y, px, py;

    static void compute(T a, T b)
    {
        if (b == 0)
        {
            d = a, x = 1, y = 0;
        }
        else
        {
            compute(b, a % b);

            px = x, py = y;
            x = py, y = px - py * (a / b);
        }
    }
};

template<typename T>
T bmultiply(T a, T b, T mod)
{
    a = (a % mod + mod) % mod;
    b = (b % mod + mod) % mod;

    T ans = 0;
    while (b > 0)
    {
        if (b & 1)
        {
            ans = (ans + a) % mod;
        }

        a = (a + a) % mod;
        b >>= 1;
    }

    return ans;
}

i64 excrt(i32 n)
{
    i64 tail = 0, lcm = 1, tmp, b, c, x0;
    for (i32 i = 1; i <= n; i++)
    {
        b = m[i];
        c = ((r[i] - tail) % b + b) % b;

        exgcd<i64>::compute(lcm, b);
        if (c % exgcd<i64>::d != 0)
        {
            return -1;
        }

        x0 = bmultiply(exgcd<i64>::x, c / exgcd<i64>::d, b / exgcd<i64>::d);
        tmp = lcm * (b / exgcd<i64>::d);
        tail = (tail + bmultiply(x0, lcm, tmp)) % tmp;
        lcm = tmp;
    }

    return tail;
}

void solve()
{
    std::cin >> k;
    for (i32 i = 1; i <= k; i++)
    {
        std::cin >> r[i];
    }

    for (i32 i = 1; i <= k; i++)
    {
        std::cin >> m[i];
    }

    for (i32 i = 1; i <= k; i++)
    {
        r[i] = (r[i] % m[i] + m[i]) % m[i];
    }

    std::cout << excrt(k) << "\n";
}

i32 main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    t = 1;
    while (t--)
    {
        solve();
    }
}