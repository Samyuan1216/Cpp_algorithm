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
    constexpr i32 MAXN = 20;
    
    // 申请额外空间的做法（用于对数器验证）
    auto shuffle1 = [](vi32& arr, i32 l, i32 r)
    {
        i32 n = r - l + 1;
        vi32 help(n);
        for (i32 l1 = l, r1 = (l + r) / 2 + 1, j = 0; j < n; l1++, r1++)
        {
            help[j++] = arr[r1];
            help[j++] = arr[l1];
        }
        for (i32 i = l, j = 0; j < n; i++, j++)
        {
            arr[i] = help[j];
        }
    };
    
    // 完美洗牌算法
    auto shuffle2 = [&](vi32& arr, i32 l, i32 r)
    {
        vi32 start(MAXN);
        vi32 split(MAXN);
        i32 size = 0;
        
        // 旋转函数
        auto rotate = [&](vi32& arr, i32 l, i32 m, i32 r)
        {
            std::reverse(arr.begin() + l, arr.begin() + m + 1);
            std::reverse(arr.begin() + m + 1, arr.begin() + r + 1);
            std::reverse(arr.begin() + l, arr.begin() + r + 1);
        };
        
        // 计算目标位置
        auto to = [](i32 i, i32 l, i32 r) -> i32
        {
            if (i <= (l + r) >> 1)
            {
                return i + (i - l + 1);
            }
            else
            {
                return i - (r - i + 1);
            }
        };
        
        // 环形调整
        auto circle = [&](vi32& arr, i32 l, i32 r, i32 i)
        {
            for (i32 j = 1; j <= i; j++)
            {
                i32 init = l + start[j] - 1;
                i32 cur = init;
                i32 next = to(cur, l, r);
                i32 curv = arr[cur];
                while (next != init)
                {
                    i32 nextv = arr[next];
                    arr[next] = curv;
                    curv = nextv;
                    cur = next;
                    next = to(cur, l, r);
                }
                arr[init] = curv;
            }
        };
        
        // 构建start和split数组
        auto build = [&](i32 n)
        {
            size = 0;
            for (i32 s = 1, p = 2; p <= n; s *= 3, p = s * 3 - 1)
            {
                start[++size] = s;
                split[size] = p;
            }
        };
        
        i32 n = r - l + 1;
        build(n);
        for (i32 i = size, m; n > 0;)
        {
            if (split[i] <= n)
            {
                m = (l + r) / 2;
                rotate(arr, l + split[i] / 2, m, m + split[i] / 2);
                circle(arr, l, l + split[i] - 1, i);
                l += split[i];
                n -= split[i];
            }
            else
            {
                i--;
            }
        }
    };
    
    // 生成随机数组
    auto randomArray = [](i32 n, i32 v) -> vi32
    {
        vi32 ans(n);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, v - 1);
        for (i32 i = 0; i < n; i++)
        {
            ans[i] = dis(gen);
        }
        return ans;
    };
    
    // 拷贝数组
    auto copyArray = [](const vi32& arr) -> vi32
    {
        return vi32(arr);
    };
    
    // 测试
    i32 n = 10000;
    i32 v = 100000;
    vi32 arr1 = randomArray(n, v);
    vi32 arr2 = copyArray(arr1);
    i32 test = 50000;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, n - 1);
    
    std::cout << "测试开始\n";
    for (i32 i = 1; i <= test; i++)
    {
        i32 a = dis(gen);
        i32 b = dis(gen);
        i32 l = std::min(a, b);
        i32 r = std::max(a, b);
        if (((r - l + 1) & 1) == 0)
        {
            shuffle1(arr1, l, r);
            shuffle2(arr2, l, r);
        }
    }
    
    for (i32 i = 0; i < n; i++)
    {
        if (arr1[i] != arr2[i])
        {
            std::cout << "出错了!\n";
            return;
        }
    }
    std::cout << "测试结束\n";
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