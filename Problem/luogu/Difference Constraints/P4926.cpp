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
    i32 cnt = 1;
public:
    vi32 head, next, to;
    std::vector<T> weight;

    Graph(i32 n, i32 m): head(n + 1), next(m + 1), to(m + 1), weight(m + 1) {}

    void add_edge(i32 u, i32 v, T w = 1)
    {
        next[cnt] = head[u];
        to[cnt] = v;
        weight[cnt] = w;
        head[u] = cnt++;
    }

    struct EdgeIterator
    {
        Graph& g;
        i32 eid;
        
        bool operator!=(i32 end) const {return eid != end;}
        auto operator*() {return std::pair<const i32&, T&>{g.to[eid], g.weight[eid]};}
        void operator++() {eid = g.next[eid];}
    };
    
    struct EdgeRange
    {
        Graph& g;
        i32 u;
        
        EdgeIterator begin() {return {g, g.head[u]};}
        i32 end() {return 0;}
    };
    
    EdgeRange operator[](i32 u) {return {*this, u};}
};

template<typename G, typename T, typename F>
pair<bool, std::vector<T>> spfa(G &g, i32 s, i32 n, T init, F check)
{
    std::vector<T> dist(n + 1, init);
    vi32 update(n + 1);
    vb enter(n + 1);
    queue<i32> que;

    dist[s] = 0, update[s] = 1, enter[s] = true;
    que.push(s);
    while (!que.empty())
    {
        i32 u = que.front();
        que.pop();

        enter[u] = false;
        for (auto [v, w]: g[u])
        {
            if (check(dist[u], w, dist[v]))
            {
                dist[v] = dist[u] + w;
                if (!enter[v])
                {
                    if (++update[v] > n)
                    {
                        return {true, std::move(dist)};
                    }

                    que.push(v);
                    enter[v] = true;
                }
            }
        }
    }

    return {false, std::move(dist)};
}

template<typename T, typename F>
T find(T l, T r, T SML, F check)
{
    T ans = l - 1, mid;
    while (r - l >= SML)
    {
        mid = l + (r - l) / 2;
        if (check(mid))
        {
            ans = mid;
            l = mid + SML;
        }
        else
        {
            r = mid - SML;
        }
    }

    return ans;
}

void solve()
{
    i32 n, m1, m2;
    std::cin >> n >> m1 >> m2;
    
    v2i32 vow(m1 + 1, vi32(4)), score(m2 + 1, vi32(2));
    for (i32 i = 1; i <= m1; i++)
    {
        std::cin >> vow[i][0] >> vow[i][1] >> vow[i][2] >> vow[i][3];
    }

    for (i32 i = 1; i <= m2; i++)
    {
        std::cin >> score[i][0] >> score[i][1];
    }

    auto check = [&](f64 limit)
    {
        Graph<f64> g(n + 2, n + m1 + 2 * m2);
        for (i32 i = 1; i <= n; i++)
        {
            g.add_edge(0, i, 0);
        }

        for (i32 i = 1; i <= m1; i++)
        {
            if (vow[i][0] == 1)
            {
                if (-limit + vow[i][3] >= 0)
                {
                    g.add_edge(vow[i][1], vow[i][2], -std::log(-limit + vow[i][3]));
                }
            }
            else
            {
                g.add_edge(vow[i][1], vow[i][2], std::log(limit + vow[i][3] - 1e-6));
            }
        }

        for (i32 i = 1; i <= m2; i++)
        {
            g.add_edge(n + 1, score[i][0], std::log(score[i][1]));
            g.add_edge(score[i][0], n + 1, -std::log(score[i][1]));
        }

        auto [status, _] = spfa(g, 0, n + 2, 1e10, [](f64 u, f64 w, f64 v)
        {
            return u + w < v;
        });
        return status;
    };

    f64 ans = find(0.0, 1e10, 1e-6, check);
    if (ans <= 0)
    {
        std::cout << -1 << "\n";
    }
    else
    {
        std::cout << ans << "\n";
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