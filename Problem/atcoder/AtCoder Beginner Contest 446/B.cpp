#include <bits/stdc++.h>
#include <bits/extc++.h>
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
using vs = std::vector<std::string>;

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

// 哈希表
class custom_hash
{
    // 核心混合函数（64 位）
    static u64 splitmix64(u64 x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;

        return x ^ (x >> 31);
    }

    // 全局随机种子（程序启动时生成，每次运行不同）
    static u64 rng()
    {
        static const u64 FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return FIXED_RANDOM;
    }
public:
    // ---------- 整数类型（所有内置整数）----------
    template<std::integral T>
    size_t operator()(T x) const
    {
        return splitmix64(static_cast<u64>(x) + rng());
    }

    // ---------- 字符串 ----------
    size_t operator()(const std::string &s) const
    {
        u64 h = rng();
        for (unsigned char c: s)
        {
            h = splitmix64(h + c);
        }

        return h;
    }

    // ---------- pair ----------
    template<class A, class B>
    size_t operator()(const std::pair<A, B> &p) const
    {
        u64 h = rng();
        h = splitmix64(h + (*this)(p.first));
        h = splitmix64(h + (*this)(p.second));

        return h;
    }

    // ---------- tuple ----------
    template<class... Ts>
    size_t operator()(const std::tuple<Ts...> &t) const
    {
        u64 h = rng();
        std::apply([&](const auto&... args)
        {
            ((h = splitmix64(h + (*this)(args))), ...);
        }, t);

        return h;
    }
};

template<typename T1, typename T2 = __gnu_pbds::null_type>
using hash_table = __gnu_pbds::gp_hash_table<T1, T2, custom_hash>;

// 平衡树
template<typename T1, typename T2 = __gnu_pbds::null_type, typename F1 = std::less<T1>>
using rb_tree = __gnu_pbds::tree<T1, T2, F1, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

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
    void sp([[maybe_unused]] const std::string& str = "") {}
} dout;
#define debug(x)
#endif

void solve()
{
    i32 n, m;
    std::cin >> n >> m;

    vb visited(m + 1);
    for (i32 i = 0, l; i < n; i++)
    {
        std::cin >> l;

        bool status = false;
        for (i32 j = 0, x = -1; j < l; j++)
        {
            std::cin >> x;
            if (!status && !visited[x])
            {
                std::cout << x << "\n";
                visited[x] = status = true;
            }
        }

        if (!status)
        {
            std::cout << 0 << "\n";
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
