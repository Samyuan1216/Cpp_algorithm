// https://vjudge.net/problem/POJ-2985#author=0

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

template<typename T = i32, typename F = std::plus<T>>
class BIT
{
private:
    i32 n;
    T init;
    F compute;
    std::vector<T> tree;

    static constexpr i32 lowbit(i32 i)
    {
        return i & -i;
    }
public:
    BIT(i32 size, F func = F{}, T i = T{}): n(size), init(i), compute(func), tree(size + 1, i) {}

    void update(i32 i, T v)
    {
        while (i <= n)
        {
            tree[i] = compute(tree[i], v);
            i += lowbit(i);
        }
    }

    T query(i32 i)
    {
        T ans = init;
        while (i > 0)
        {
            ans = compute(ans, tree[i]);
            i -= lowbit(i);
        }

        return ans;
    }
};

class DSU
{
    vi32 father, size;
public:
    DSU(i32 n): father(n + 1), size(n + 1, 1)
    {
        for (i32 i = 1; i <= n; i++)
        {
            father[i] = i;
        }
    }

    i32 find(i32 i)
    {
        if (i != father[i])
        {
            father[i] = find(father[i]);
        }

        return father[i];
    }

    void merge(i32 x, i32 y)
    {
        i32 fx = find(x), fy = find(y);
        if (fx == fy)
        {
            return;
        }

        if (size[fx] < size[fy])
        {
            std::swap(fx, fy);
        }

        father[fy] = fx;
        size[fx] += size[fy];
    }

    i32 get_size(i32 i)
    {
        return size[find(i)];
    }

    bool is_same(i32 x, i32 y)
    {
        return find(x) == find(y);
    }
};

void solve()
{
    i32 n, m;
    std::cin >> n >> m;

    BIT tree(n);
    tree.update(1, n);

    DSU uf(n);
    i32 num = n;

    while (m--)
    {
        i32 op;
        std::cin >> op;

        if (op == 0)
        {
            i32 i, j;
            std::cin >> i >> j;

            if (uf.is_same(i, j))
            {
                continue;
            }

            num--;
            tree.update(uf.get_size(i), -1);
            tree.update(uf.get_size(j), -1);
            uf.merge(i, j);
            tree.update(uf.get_size(i), 1);
        }
        else
        {
            i32 k;
            std::cin >> k;

            k = num - k + 1;
            auto check = [&](auto &mid)
            {
                return tree.query(mid) >= k;
            };

            auto find = [&](auto l, auto r)
            {
                std::optional<decltype(l)> ans;
                while (l <= r)
                {
                    auto mid = l + (r - l) / 2;
                    if (check(mid))
                    {
                        ans = mid;
                        r = mid - 1;
                    }
                    else
                    {
                        l = mid + 1;
                    }
                }
            
                return ans;
            };

            std::cout << *find(1, n) << "\n";
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
