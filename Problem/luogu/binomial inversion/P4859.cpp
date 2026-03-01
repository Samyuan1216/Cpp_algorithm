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
std::vector<T> get_fact(i32 n, T mod)
{
    std::vector<T> fac(n + 1);

    fac[0] = fac[1] = 1;
    for (i32 i = 2; i <= n; i++)
    {
        fac[i] = ((i128)i * fac[i - 1]) % mod;
    }

    return std::move(fac);
}

template<typename T>
std::vector<std::vector<T>> C(i32 n, T mod)
{
    std::vector<std::vector<T>> c(n + 1, std::vector<T>(n + 1));
    for (i32 i = 0; i <= n; i++)
    {
        c[i][0] = 1;
        for (i32 j = 1; j <= i; j++)
        {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
        }
    }

    return std::move(c);
}

void solve()
{
    constexpr i64 mod = 1000000009;
    i32 n, k;
    std::cin >> n >> k;

    vi32 a(n + 1);
    for (i32 i = 1; i <= n; i++)
    {
        std::cin >> a[i];
    }

    vi32 b(n + 1);
    for (i32 i = 1; i <= n; i++)
    {
        std::cin >> b[i];
    }

    if ((n + k) & 1)
    {
        std::cout << 0 << "\n";
        return;
    }

    k = (n + k) / 2;
    auto fac = get_fact(n, mod);
    auto c = C(n, mod);

    ranges::sort(a.begin() + 1, a.end());
    ranges::sort(b.begin() + 1, b.end());

    vi64 small(n + 1);
    for (i32 i = 1, cnt = 0; i <= n; i++)
    {
        while (cnt + 1 <= n && a[i] > b[cnt + 1])
        {
            cnt++;
        }

        small[i] = cnt;
    }

    v2i64 dp(n + 1, vi64(n + 1));
    dp[0][0] = 1;
    for (i32 i = 1; i <= n; i++)
    {
        dp[i][0] = dp[i - 1][0];
        for (i32 j = 1; j <= i; j++)
        {
            dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1] * (small[i] - j + 1) % mod) % mod;
        }
    }

    vi64 g(n + 1);
    for (i32 i = 0; i <= n; i++)
    {
        g[i] = fac[n - i] * dp[n][i] % mod;
    }

    i64 ans = 0;
    for (i32 i = k; i <= n; i++)
    {
        if ((i - k) & 1)
        {
            ans = (ans + c[i][k] * g[i] % mod * (mod - 1) % mod) % mod;
        }
        else
        {
            ans = (ans + c[i][k] * g[i] % mod) % mod;
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