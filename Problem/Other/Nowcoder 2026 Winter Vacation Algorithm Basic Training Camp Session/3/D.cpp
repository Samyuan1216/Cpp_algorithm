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

void shenzouz()
{
    i32 n, m;
    std::cin >> n >> m;

    auto get_num = [&](i32 x, i32 y)
    {
        if (x == 0)
        {
            return 1;
        }
        else if (y == m - 1)
        {
            return 2;
        }
        else if (x == n - 1)
        {
            return 3;
        }
        else if(y == 0)
        {
            return 4;
        }

        return 0;
    };

    v2i32 arr(4, vi32(4));
    bool status = false;
    for (i32 i = 0, index = 0, x; i < n; i++)
    {
        string str;
        std::cin >> str;
        for (i32 j = 0; j < m; j++)
        {
            x = str[j] - '0';
            if (x != 0)
            {
                arr[index][0] = i;
                arr[index][1] = j;
                arr[index][2] = x;

                auto num = get_num(i, j);
                arr[index++][3] = num;
                if (num == 0)
                {
                    status = true;
                }
            }
        }
    }

    auto check = [&]()
    {
        auto get = [&](i32 r, i32 c)
        {
            for (i32 i = 0; i < 4; i++)
            {
                if (arr[i][0] == r && arr[i][1] == c)
                {
                    return arr[i][2];
                }
            }

            return 0;
        };
        
        auto bc = [&](i32 r, i32 c, i32 r1, i32 c1, i32 r2, i32 c2)
        {
            i32 x = get(r, c);
            if (x == 0)
            {
                return false;
            }

            i32 y = 3 - x;
            return get(r1, c1) == y && get(r2, c2) == y;
        };
        
        if (bc(0, 0, 0, 1, 1, 0) || bc(0, m-1, 0, m-2, 1, m-1) || bc(n-1, 0, n-2, 0, n-1, 1) || bc(n-1, m-1, n-2, m-1, n-1, m-2))
        {
            return false;
        }
        
        for (i32 i = 0; i + 1 < n; i++)
        {
            for (i32 j = 0; j + 1 < m; j++)
            {
                i32 a = get(i, j), b = get(i, j+1), c = get(i+1, j), d = get(i+1, j+1);
                if (a && a == d && b && b == c && a != b)
                {
                    return false;
                }
            }
        }
        
        return true;
    };

    if (!check())
    {
        std::cout << "NO\n";
        return;
    }

    if (status)
    {
        std::cout << "YES\n";
        return;
    }

    ranges::sort(arr, [](auto &a, auto &b)
    {
        if (a[3] != b[3])
        {
            return a[3] < b[3];
        }

        if (a[3] == 1)
        {
            return a[1] < b[1];
        }

        if (a[3] == 2)
        {
            return a[0] < b[0];
        }

        if (a[3] == 3)
        {
            return a[1] > b[1];
        }

        if (a[3] == 4)
        {
            return a[0] > b[0];
        }

        return true;
    });

    if (arr[0][2] != arr[2][2])
    {
        std::cout << "YES\n";
    }
    else
    {
        std::cout << "NO\n";
    }
}

i32 main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    i32 t = 1;
    std::cin >> t;
    while (t--)
    {
        shenzouz();
    }
}
