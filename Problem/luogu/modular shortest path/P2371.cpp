#include <bits/stdc++.h>
namespace ranges = std::ranges;

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

// 两次转圈
template<typename T>
T gcd(T a, T b)
{
    return (b == 0? a: gcd(b, a % b));
}

void solve()
{
    constexpr i64 inf = INT64_MAX;
    i32 n;
    i64 l, r;

    std::cin >> n >> l >> r;
    l--;

    vi32 v(n);
    for (auto &num: v)
    {
        std::cin >> num;
    }

    ranges::sort(v);
    v.erase(v.begin(), ranges::lower_bound(v, 1));

    n = v.size();
    if (n == 0)
    {
        std::cout << 0 << "\n";
        return;
    }

    i32 x = v[0];
    vi64 dist(x + 1, inf);
    dist[0] = 0;

    for (i32 i = 1, d; i < n; i++)
    {
        d = gcd(v[i], x);
        for (i32 j = 0; j < d; j++)
        {
            for (i32 cur = j, next, circle = 0; circle < 2; circle += (cur == j)? 1: 0)
            {
                next = (cur + v[i]) % x;
                if (dist[cur] != inf)
                {
                    dist[next] = std::min(dist[next], dist[cur] + v[i]);
                }

                cur = next;
            }
        }
    }

    i64 ans = 0;
    for (i32 i = 0; i < x; i++)
    {
        if (r >= dist[i])
        {
            ans += (r - dist[i]) / x + 1;
        }

        if (l >= dist[i])
        {
            ans -= (l - dist[i]) / x + 1;
        }
    }

    std::cout << ans << "\n";
}

// dijkstra
// template<typename T>
// class Graph
// {
//     i32 cnt = 1;
// public:
//     vi32 head, next, to;
//     std::vector<T> weight;

//     Graph(i32 n, i32 m): head(n + 1), next(m + 1), to(m + 1), weight(m + 1) {}

//     void add_edge(i32 u, i32 v, T w = 1)
//     {
//         next[cnt] = head[u];
//         to[cnt] = v;
//         weight[cnt] = w;
//         head[u] = cnt++;
//     }

//     struct EdgeIterator
//     {
//         Graph& g;
//         i32 eid;
        
//         bool operator!=(i32 end) const {return eid != end;}
//         auto operator*() {return std::pair<const i32&, T&>{g.to[eid], g.weight[eid]};}
//         void operator++() {eid = g.next[eid];}
//     };
    
//     struct EdgeRange
//     {
//         Graph& g;
//         i32 u;
        
//         EdgeIterator begin() {return {g, g.head[u]};}
//         i32 end() {return 0;}
//     };
    
//     EdgeRange operator[](i32 u) {return {*this, u};}
// };

// template<typename T, typename F1, typename F2>
// std::vector<T> dijkstra(Graph<T> &g, i32 n, i32 s, T init, F1 check, F2 update)
// {
//     std::vector<T> distance(n + 1, init);
//     pq<pair<i32, T>, F1> heap(check);
//     vb visited(n + 1);

//     distance[s] = 0;
//     heap.push({s, 0});

//     while (!heap.empty())
//     {
//         auto [u, wu] = heap.top();
//         heap.pop();

//         if (visited[u] == true)
//         {
//             continue;
//         }

//         visited[u] = true;
//         for (auto [v, wv]: g[u])
//         {
//             if (!visited[v])
//             {
//                 auto [new_dist, status] = update(wu, wv, distance[v]);
//                 if (status)
//                 {
//                     distance[v] = new_dist;
//                     heap.push({v, distance[v]});
//                 }
//             }
//         }
//     }

//     return std::move(distance);
// }

// void solve()
// {
//     constexpr i64 inf = INT64_MAX;
//     i32 n, x = 0;
//     i64 l, r;
    
//     std::cin >> n >> l >> r;
//     l--;

//     vi32 v(n + 1);
//     for (i32 i = 1; i <= n; i++)
//     {
//         std::cin >> v[i];
//         if (v[i] != 0 && x == 0)
//         {
//             x = v[i];
//             v[i] = 0;
//         }
//     }

//     Graph<i64> g(x, n * x);
//     for (i32 i = 1; i <= n; i++)
//     {
//         if (v[i] != 0)
//         {
//             for (i32 j = 0; j < x; j++)
//             {
//                 g.add_edge(j, (j + v[i]) % x, v[i]);
//             }
//         }
//     }

//     auto check = [](auto &a, auto &b)
//     {
//         return a.second > b.second;
//     };

//     auto update = [](auto &a, auto &b, auto &c)
//     {
//         return std::make_pair(a + b, a + b < c);
//     };

//     auto dist = dijkstra(g, x, 0, inf, check, update);

//     i64 ans = 0;
//     for (i32 i = 0; i < x; i++)
//     {
//         if (r >= dist[i])
//         {
//             ans += (r - dist[i]) / x + 1;
//         }

//         if (l >= dist[i])
//         {
//             ans -= (l - dist[i]) / x + 1;
//         }
//     }

//     std::cout << ans << "\n";
// }

i32 main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    i32 t = 1;
    while (t--)
    {
        solve();
    }
}