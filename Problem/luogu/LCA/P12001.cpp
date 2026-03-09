#include <bits/stdc++.h>
#include <bits/extc++.h>
namespace ranges = std::ranges;
namespace views = std::views;

using i64 = int64_t;

template<typename T>
using lim = std::numeric_limits<T>;

#ifndef YUAN_DEBUG
struct __X
{
    __X& operator<<(const auto& str) {return *this;}
    void sp([[maybe_unused]] const std::string& str = "") {}
} dout;
#define debug(x)
#endif

void solve()
{
    auto euler = [&](int n)
    {
        auto visited = std::vector<bool>(n + 1);
        auto prime = std::vector<int>(n / 2 + 1);
    
        int cnt = 0;
        for (int i = 2; i <= n; ++i)
        {
            if (!visited[i])
            {
                prime[cnt++] = i;
            }
    
            for (int j = 0; j < cnt; ++j)
            {
                if (i * prime[j] > n)
                {
                    break;
                }
    
                visited[i * prime[j]] = true;
                if (i % prime[j] == 0)
                {
                    break;
                }
            }
        }
    
        prime.resize(cnt);
        return prime;
    };

    auto prime = euler(100010);

    int n, q;
    std::cin >> n >> q;

    auto arr = std::vector<int>(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];
    }

    auto g = std::vector(n + 1, std::vector<int>());
    for (int i = 0, u, v; i < n - 1; ++i)
    {
        std::cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    auto father = std::vector<int>(n + 1);
    auto dfn = std::vector<int>(n + 1);
    int dfn_cnt = 0;

    int power = std::bit_width(unsigned(n));
    auto deep = std::vector<int>(n + 1);
    auto stjump = std::vector(n + 1, std::vector<int>(power + 1));
    
    auto dfs = [&](auto &&self, int u, int f) -> void
    {
        dfn[++dfn_cnt] = u;
        father[u] = f;

        deep[u] = deep[f] + 1;
        stjump[u][0] = f;
        for (int p = 1; (1 << p) <= deep[u]; ++p)
        {
            stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
        }
    
        for (auto v: g[u])
        {
            if (v != f)
            {
                self(self, v, u);
            }
        }
    };

    dfs(dfs, 1, 0);
    
    auto lca = [&](int a, int b)
    {
        if (deep[a] < deep[b])
        {
            std::swap(a, b);
        }
    
        for (int p = power; p >= 0; --p)
        {
            if (deep[stjump[a][p]] >= deep[b])
            {
                a = stjump[a][p];
            }
        }
    
        if (a == b)
        {
            return a;
        }
    
        for (int p = power; p >= 0; --p)
        {
            if (stjump[a][p] != stjump[b][p])
            {
                a = stjump[a][p], b = stjump[b][p];
            }
        }
    
        return stjump[a][0];
    };

    auto query = std::vector(q + 1, std::array<int, 4>());
    for (int i = 1, u, v; i <= q; ++i)
    {
        std::cin >> u >> v;

        query[i][0] = u, query[i][1] = v;
        query[i][2] = lca(u, v);
    }

    auto sum = std::vector<int>(n + 1);
    for (auto &p: prime)
    {
        for (int i = 1, u; i <= n; ++i)
        {
            u = dfn[i];
            sum[u] = sum[father[u]] + (arr[u] % p == 0? 1: 0);
        }

        for (int i = 1; i <= q; ++i)
        {
            int u = query[i][0], v = query[i][1];
            int l = query[i][2], fl = father[l];

            int count = sum[u] + sum[v] - sum[l] - sum[fl];
            if (count > 0)
            {
                ++query[i][3];
            }
        }
    }

    for (int i = 1; i <= q; ++i)
    {
        std::cout << query[i][3] << "\n";
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    while (t--)
    {
        solve();
    }
}
