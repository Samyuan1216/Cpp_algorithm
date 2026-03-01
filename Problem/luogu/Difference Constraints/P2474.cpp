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
using std::string, std::pair, std::tuple, std::queue, std::stack;

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

template<typename T>
class Graph
{
public:
    i32 n;
    std::vector<std::vector<T>> matrix;

    Graph(i32 size, T init = T{}): n(size), matrix(size + 1, std::vector<T>(size + 1, init)) {};
};

template<typename T, typename F>
void floyd(Graph<T> &g, F func)
{
    for (i32 k = 1; k <= g.n; k++)
    {
        for (i32 i = 1; i <= g.n; i++)
        {
            for (i32 j = 1; j <= g.n; j++)
            {
                g.matrix[i][j] = func(g.matrix[i][j], g.matrix[i][k] + g.matrix[k][j]);
            }
        }
    }
}

void solve()
{
    i32 n, a, b;
    std::cin >> n >> a >> b;

    Graph<i32> dmin(n), dmax(n);
    for (i32 i = 1; i <= n; i++)
    {
        string str;
        std::cin >> str;

        for (i32 j = 1; j <= n; j++)
        {
            if (str[j - 1] == '=')
            {
                dmin.matrix[i][j] = dmax.matrix[i][j] = 0;
            }
            else if (str[j - 1] == '+')
            {
                dmin.matrix[i][j] = 1, dmax.matrix[i][j] = 2;
            }
            else if (str[j - 1] == '-')
            {
                dmin.matrix[i][j] = -2, dmax.matrix[i][j] = -1;
            }
            else
            {
                dmin.matrix[i][j] = -2, dmax.matrix[i][j] = 2;
            }
        }
    }

    for (i32 i = 1; i <= n; i++)
    {
        dmin.matrix[i][i] = dmax.matrix[i][i] = 0;
    }

    floyd(dmin, [](i32 a, i32 b)
    {
        return std::max(a, b);
    });

    floyd(dmax, [](i32 a, i32 b)
    {
        return std::min(a, b);
    });

    i32 ans1 = 0, ans2 = 0, ans3 = 0;
    for (i32 i = 1; i <= n; i++)
    {
        for (i32 j = 1; j < i; j++)
        {
            if (i != a && i != b && j != a && j != b)
            {
                if (dmin.matrix[a][i] > dmax.matrix[j][b] || dmin.matrix[a][j] > dmax.matrix[i][b])
                {
                    ans1++;
                }

                if (dmax.matrix[a][i] < dmin.matrix[j][b] || dmax.matrix[a][j] < dmin.matrix[i][b])
                {
                    ans3++;
                }

                if (dmin.matrix[a][i] == dmax.matrix[a][i] && dmin.matrix[j][b] == dmax.matrix[j][b] && dmin.matrix[a][i] == dmin.matrix[j][b])
                {
                    ans2++;
                }
                else if (dmin.matrix[b][i] == dmax.matrix[b][i] && dmin.matrix[j][a] == dmax.matrix[j][a] && dmin.matrix[b][i] == dmin.matrix[j][a])
                {
                    ans2++;
                }
            }
        }
    }

    std::cout << ans1 << " " << ans2 << " " << ans3 << "\n";
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