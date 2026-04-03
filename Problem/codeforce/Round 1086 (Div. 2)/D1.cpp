#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

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

class DSU
{
    std::vector<int> father, size;
public:
    DSU(int n): father(n + 1), size(n + 1, 1)
    {
        ranges::iota(father, 0);
    }

    int find(int i)
    {
        if (i != father[i])
        {
            father[i] = find(father[i]);
        }

        return father[i];
    }

    void merge(int x, int y)
    {
        int fx = find(x), fy = find(y);
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

    int get_size(int i)
    {
        return size[find(i)];
    }

    bool same(int x, int y)
    {
        return find(x) == find(y);
    }
};

void solve()
{
    int n;
    std::cin >> n;

    auto g = std::vector(n, std::string());
    for (auto &s: g)
    {
        std::cin >> s;
    }

    auto edges = std::vector<std::array<int, 2>>();
    for (int u = 0; u < n; ++u)
    {
        for (int v = 0; v < n; ++v)
        {
            if (u == v || g[u][v] == '0')
            {
                continue;
            }

            bool status = true;
            for (int w = 0; w < n; ++w)
            {
                if (w == u || w == v)
                {
                    continue;
                }

                if (g[u][w] == '1' && g[w][v] == '1')
                {
                    status = false;
                    break;
                }
            }

            if (status)
            {
                edges.push_back({u, v});
            }
        }
    }

    if (std::ssize(edges) != n - 1)
    {
        std::cout << "No\n";
        return;
    }

    auto s = DSU(n);
    for (auto &[u, v]: edges)
    {
        if (s.same(u, v))
        {
            std::cout << "No\n";
            return;
        }

        s.merge(u, v);
    }

    auto check = std::vector(n, std::string(n, '0'));

    auto grid = std::vector(n, std::vector<int>());
    for (auto &[u, v]: edges)
    {
        grid[u].push_back(v);
    }

    auto dfs = [&](this auto &&self, const int &s, int u) -> void
    {
        check[s][u] = '1';
        for (auto &v: grid[u])
        {
            self(s, v);
        }
    };

    for (int s = 0; s < n; ++s)
    {
        dfs(s, s);
    }

    if (check == g)
    {
        std::cout << "Yes\n";

        for (auto &[u, v]: edges)
        {
            std::cout << u + 1 << " " << v + 1 << "\n";
        }
    }
    else
    {
        std::cout << "No\n";
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    std::cin >> t;
    while (t--)
    {
        solve();
    }
}
