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

class Seg
{
    struct Info
    {
        i64 max, add;
        bool update, reverse, clear;
        i32 flipped;

        Info(): max(0), add(0), update(false), reverse(false), clear(false), flipped(2) {}
    };

    std::vector<Info> info;

    void max_lazy(i32 i, i64 v)
    {
        if (info[i].flipped != 0)
        {
            info[i].max += v;
            info[i].add += v;
            info[i].update = true;
        }
    }

    void clear_lazy(i32 i)
    {
        info[i].max = 0;
        info[i].add = 0;
        info[i].update = false;
        info[i].clear = true;
    }

    void flip_lazy(i32 i)
    {
        info[i].reverse = !info[i].reverse;

        if (info[i].flipped == 0)
        {
            info[i].flipped = 2;
        }
        else if (info[i].flipped == 2)
        {
            info[i].flipped = 0;
        }
    }

    void up(i32 i)
    {
        info[i].max = std::max(info[i << 1].max, info[i << 1 | 1].max);

        if (info[i << 1].flipped != info[i << 1 | 1].flipped)
        {
            info[i].flipped = 1;
        }
        else
        {
            info[i].flipped = info[i << 1].flipped;
        }
    }

    void down(i32 i)
    {
        if (info[i].clear)
        {
            clear_lazy(i << 1);
            clear_lazy(i << 1 | 1);

            info[i].clear = false;
        }

        if (info[i].reverse)
        {
            flip_lazy(i << 1);
            flip_lazy(i << 1 | 1);

            info[i].reverse = false;
        }

        if (info[i].update)
        {
            max_lazy(i << 1, info[i].add);
            max_lazy(i << 1 | 1, info[i].add);

            info[i].add = 0;
            info[i].update = false;
        }
    }
public:
    Seg(i32 size): info((size + 1) << 2) {}

    void add(i32 jobl, i32 jobr, i64 jobv, i32 l, i32 r, i32 i)
    {
        if (l >= jobl && r <= jobr)
        {
            max_lazy(i, jobv);
        }
        else
        {
            i32 mid = l + (r - l) / 2;
            down(i);

            if (jobl <= mid)
            {
                add(jobl, jobr, jobv, l, mid, i << 1);
            }

            if (jobr >= mid + 1)
            {
                add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            }

            up(i);
        }
    }

    void reverse(i32 jobl, i32 jobr, i32 l, i32 r, i32 i)
    {
        if (l >= jobl && r <= jobr)
        {
            clear_lazy(i);
            flip_lazy(i);
        }
        else
        {
            i32 mid = l + (r - l) / 2;
            down(i);

            if (jobl <= mid)
            {
                reverse(jobl, jobr, l, mid, i << 1);
            }

            if (jobr >= mid + 1)
            {
                reverse(jobl, jobr, mid + 1, r, i << 1 | 1);
            }

            up(i);
        }
    }

    i64 query(i32 jobl, i32 jobr, i32 l, i32 r, i32 i)
    {
        if (l >= jobl && r <= jobr)
        {
            return info[i].max;
        }

        i32 mid = l + (r - l) / 2;
        down(i);

        i64 ans = lim<i64>::min();
        if (jobl <= mid)
        {
            ans = std::max(ans, query(jobl, jobr, l, mid, i << 1));
        }

        if (jobr >= mid + 1)
        {
            ans = std::max(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));
        }

        return ans;
    }
};

void solve()
{
    i32 n, q;
    std::cin >> n >> q;

    Seg tree(n);
    while (q--)
    {
        i32 op, l, r;
        std::cin >> op >> l >> r;

        if (op == 1)
        {
            i64 x;
            std::cin >> x;

            tree.add(l, r, x, 1, n, 1);
        }
        else if (op == 2)
        {
            tree.reverse(l, r, 1, n, 1);
        }
        else
        {
            std::cout << tree.query(l, r, 1, n, 1) << "\n";
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