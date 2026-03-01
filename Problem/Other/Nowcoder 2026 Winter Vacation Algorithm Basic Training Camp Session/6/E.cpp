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

    bool same(i32 x, i32 y)
    {
        return find(x) == find(y);
    }
};

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

template<typename T = i32>
class Graph
{
    std::vector<std::vector<pair<u32, T>>> adj;
public:
    Graph(u32 n): adj(n + 1) {}

    void add_edge(u32 u, u32 v, T w = T{})
    {
        adj[u].emplace_back(v, w);
    }

    [[nodiscard]] std::vector<pair<u32, T>>& operator[](i32 u)
    {
        return adj[u];
    }
};

void solve()
{
    i32 n, m, x, d;
    std::cin >> n >> m >> x >> d;

    pq<ai32<2>, decltype([](auto &a, auto &b)
    {
        return a[1] < b[1];
    })> heap;

    for (i32 i = 1, x; i <= n; i++)
    {
        std::cin >> x;
        heap.push({i, x});
    }

    Graph g(n);
    for (i32 i = 1, u, v; i <= m; i++)
    {
        std::cin >> u >> v;

        g.add_edge(u, v);
        g.add_edge(v, u);
    }

    vi32 h(x);
    for (auto &hx: h)
    {
        std::cin >> hx;
    }

    ranges::sort(h, std::greater<i32>());

    DSU uf(n);
    vb visited(n + 1);

    BIT tree(n);

    i32 num = 0;
    vi32 ans(x);

    for (i32 i = 0; i < x; ++i)
    {
        i32 hx = h[i];
        while (!heap.empty() && heap.top()[1] > hx)
        {
            i32 u = heap.top()[0];
            heap.pop();

            visited[u] = true;
            num++;
            tree.update(1, 1);

            for (auto [v, w]: g[u])
            {
                if (visited[v] && !uf.same(u, v))
                {
                    i32 sz_u = uf.get_size(u);
                    i32 sz_v = uf.get_size(v);

                    tree.update(sz_u, -1);
                    tree.update(sz_v, -1);

                    uf.merge(u, v);

                    tree.update(sz_u + sz_v, 1);
                    num--;
                }
            }
        }

        ans[i] = num - tree.query(d - 1);
    }

    for (i32 i = x - 1; i >= 0; --i)
    {
        std::cout << ans[i] << "\n";
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
