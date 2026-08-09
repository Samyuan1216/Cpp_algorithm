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
    for (int i = 0; auto &[w, u, v]: edges)
    {
        std::cin >> u >> v;
        --u, --v;

        w = ++i;
    }

    ranges::sort(edges);

    std::vector<int> father(2 * n);
    ranges::iota(father, 0);

    auto find = [&](this auto &&find, int i) -> int
    {
        return (father[i] = (father[i] == i? i: find(father[i])));
    };

    std::vector<std::vector<int>> g(2 * n);
    std::vector<int> weight(2 * n);
    int cnt = n;

    for (int i = 0; i < m; ++i)
    {
        if (int fx = find(edges[i][1]), fy = find(edges[i][2]); fx != fy)
        {
            g[cnt].push_back(fx);
            g[cnt].push_back(fy);

            father[fx] = cnt;
            father[fy] = cnt;
            weight[cnt] = edges[i][0];

            ++cnt;
        }
    }

    constexpr int limit = 20;
    auto stjump = std::vector(2 * n, std::vector<int>(limit));
    std::vector<int> size(2 * n);

    [&](this auto &&dfs, int u, int f) -> void
    {
        stjump[u][0] = f;
        size[u] = (u < n? 1: 0);

        for (auto &v: g[u])
        {
            dfs(v, u);

            size[u] += size[v];
        }
    } (cnt - 1, cnt - 1);

    for (int p = 1; p < limit; ++p)
    {
        for (int i = 0; i < cnt; ++i)
        {
            stjump[i][p] = stjump[stjump[i][p - 1]][p - 1];
        }
    }

    auto check = [&](int mid, int x, int y, int z) -> bool
    {
        for (int p = limit - 1; p >= 0; --p)
        {
            if (weight[stjump[x][p]] <= mid)
            {
                x = stjump[x][p];
            }

            if (weight[stjump[y][p]] <= mid)
            {
                y = stjump[y][p];
            }
        }

        int cnt = (x == y? size[x]: size[x] + size[y]);
        return cnt >= z;
    };

    auto bs = [&](int x, int y, int z) -> int
    {
        int l = 1, r = m, ans = m;
        while (l <= r)
        {
            int mid = std::midpoint(l, r);
            if (check(mid, x, y, z))
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

    int q;
    std::cin >> q;

    while (q--)
    {
        int x, y, z;
        std::cin >> x >> y >> z;
        --x, --y;

        std::cout << bs(x, y, z) << "\n";
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
