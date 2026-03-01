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

constexpr int MAXN = 100010;
vi64 hp(MAXN), recovery(MAXN), reward(MAXN), init(MAXN), attack(MAXN);
std::map<i64, i32> sorted;
i32 t, n, m;

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

pair<i64, i64> excrt(i32 n)
{
    i64 tail = 0, lcm = 1, tmp, a, b, c, x0;
    for (i32 i = 1; i <= n; i++)
    {
        a = bmultiply(attack[i], lcm, recovery[i]);
        b = recovery[i];
        c = ((hp[i] - attack[i] * tail) % b + b) % b;

        exgcd<i64>::compute(a, b);
        if (c % exgcd<i64>::d != 0)
        {
            return {-1, -1};
        }

        x0 = bmultiply(exgcd<i64>::x, c / exgcd<i64>::d, b / exgcd<i64>::d);
        tmp = lcm * (b / exgcd<i64>::d);
        tail = (tail + bmultiply(x0, lcm, tmp)) % tmp;
        lcm = tmp;
    }

    return {lcm, tail};
}

i64 allocate(i32 n, i32 m)
{
    sorted.clear();
    for (i32 i = 1; i <= m; i++)
    {
        sorted[init[i]]++;
    }

    i64 maxn = 0;
    for (i32 i = 1; i <= n; i++)
    {
        auto iter = sorted.upper_bound(hp[i]);
        if (iter != sorted.begin())
        {
            iter--;
        }

        i64 sword = iter->first;
        attack[i] = sword;
        if (--sorted[sword] == 0)
        {
            sorted.erase(sword);
        }

        sorted[reward[i]]++;
        maxn = std::max(maxn, (hp[i] + attack[i] - 1) / attack[i]);
        hp[i] %= recovery[i];
    }

    return maxn;
}

void solve()
{
    std::cin >> n >> m;
    for (i32 i = 1; i <= n; i++)
    {
        std::cin >> hp[i];
    }

    for (i32 i = 1; i <= n; i++)
    {
        std::cin >> recovery[i];
    }

    for (i32 i = 1; i <= n; i++)
    {
        std::cin >> reward[i];
    }

    for (i32 i = 1; i <= m; i++)
    {
        std::cin >> init[i];
    }

    i64 maxn = allocate(n, m);
    auto [lcm, tail] = excrt(n);

    i64 ans = (tail == -1 || tail >= maxn? tail: (maxn - tail + lcm - 1) / lcm * lcm + tail);
    std::cout << ans << "\n";
}

i32 main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> t;
    while (t--)
    {
        solve();
    }
}