#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

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
    int n, m;
    std::cin >> n >> m;

    std::vector<std::array<int, 3>> edges(m);
    std::vector<int> degree(n);
    i64 sum = 0;

    for (auto &[u, v, w]: edges)
    {
        std::cin >> u >> v >> w;
        --u, --v;

        sum += w;
        ++degree[u], ++degree[v];
    }

    int cntd = 0;
    for (auto &x: degree)
    {
        if (x & 1)
        {
            ++cntd;
        }
    }

    if (cntd == 0)
    {
        std::cout << sum << "\n";
        return;
    }

    std::vector<int> father(n + m);
    ranges::iota(father, 0);

    auto find = [&](this auto &&find, int i) -> int
    {
        return father[i] = (father[i] == i? i: find(father[i]));
    };

    std::vector<std::vector<int>> g(n + m);
    std::vector<int> weight(n + m);
    int cnt = n;

    for (auto &[u, v, w]: edges)
    {
        if (int fx = find(u), fy = find(v); fx != fy)
        {
            father[fx] = father[fy] = cnt;
            weight[cnt] = w;

            g[cnt].push_back(fx);
            g[cnt].push_back(fy);

            ++cnt;
        }
        else
        {
            father[fx] = cnt;
            weight[cnt] = w;

            g[cnt].push_back(fx);

            ++cnt;
        }
    }

    std::vector<int> minf(n + m);
    [&](this auto &&dfs, int u, int min) -> void
    {
        minf[u] = std::min(weight[u], min);
        for (auto &v: g[u])
        {
            dfs(v, minf[u]);
        }
    } (n + m - 1, weight[n + m - 1]);

    [&](this auto &&dfs, int u) -> int
    {
        if (u < n)
        {
            return degree[u] & 1;
        }

        int num = 0;
        for (auto &v: g[u])
        {
            num += dfs(v);
        }

        sum += (num / 2) * minf[u];
        return num % 2;
    } (n + m - 1);

    std::cout << sum << "\n";
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
