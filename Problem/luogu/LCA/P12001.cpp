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
        std::vector<bool> visited(n + 1);
        std::vector<int> prime(n / 2 + 1);
        std::vector<int> min_prime(n + 1, -1);
    
        int cnt = 0;
        for (int i = 2; i <= n; ++i)
        {
            if (!visited[i])
            {
                min_prime[i] = cnt;
                prime[cnt++] = i;
            }
    
            for (int j = 0; j < cnt; ++j)
            {
                if (i * prime[j] > n)
                {
                    break;
                }
    
                visited[i * prime[j]] = true;
                min_prime[i * prime[j]] = j;
                if (i % prime[j] == 0)
                {
                    break;
                }
            }
        }
    
        prime.resize(cnt);
        return std::pair{prime, min_prime};
    };

    auto [prime, min_prime] = euler(100010);

    int n, q;
    std::cin >> n >> q;

    auto arr = std::vector<std::bitset<10000>>(n + 1);
    for (int i = 1, x; i <= n; ++i)
    {
        std::cin >> x;
        while (x > 1)
        {
            arr[i].set(min_prime[x]);
            x /= prime[min_prime[x]];
        }
    }

    auto g = std::vector(n + 1, std::vector<int>());
    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    int power = std::bit_width(unsigned(n));
    auto deep = std::vector<int>(n + 1);
    auto stjump = std::vector(n + 1, std::vector<int>(power + 1));
    auto stprime = std::vector(n + 1, std::vector<std::bitset<10000>>(power + 1));

    auto dfs = [&](auto &&self, int u, int f) -> void
    {
        deep[u] = deep[f] + 1;
        stjump[u][0] = f;
        stprime[u][0] = arr[u];

        for (int p = 1; (1 << p) <= deep[u]; ++p)
        {
            stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
            stprime[u][p] = stprime[u][p - 1] | stprime[stjump[u][p - 1]][p - 1];
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
    
        std::bitset<10000> ans;
        for (int p = power; p >= 0; --p)
        {
            if (deep[stjump[a][p]] >= deep[b])
            {
                ans |= stprime[a][p];
                a = stjump[a][p];
            }
        }
    
        if (a == b)
        {
            ans |= arr[a];
            return ans;
        }
    
        for (int p = power; p >= 0; --p)
        {
            if (stjump[a][p] != stjump[b][p])
            {
                ans |= stprime[a][p] | stprime[b][p];
                a = stjump[a][p], b = stjump[b][p];
            }
        }
    
        ans |= stprime[a][0] | stprime[b][0] | arr[stjump[a][0]];
        return ans;
    };

    while (q--)
    {
        int u, v;
        std::cin >> u >> v;
        std::cout << lca(u, v).count() << "\n";
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
