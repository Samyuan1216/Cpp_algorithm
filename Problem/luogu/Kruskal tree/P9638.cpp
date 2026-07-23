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
    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<std::array<int, 4>> edges(m);
    for (int i = 0; auto &[w, u, v, id]: edges)
    {
        std::cin >> u >> v >> w;
        --u, --v;

        id = i++;
    }

    ranges::sort(edges, std::greater());

    std::vector<int> father(n << 1);
    ranges::iota(father, 0);

    auto find = [&](this auto &&find, int i) -> int
    {
        return (father[i] = (father[i] == i? i: find(father[i])));
    };

    std::vector<std::vector<int>> g(n << 1);
    std::vector<int> w(n << 1), eton(m, -1);

    for (int i = 0, j = n; i < m; ++i)
    {
        if (int fx = find(edges[i][1]), fy = find(edges[i][2]); fx != fy)
        {
            father[fx] = father[fy] = j;
            w[j] = edges[i][0];
            eton[edges[i][3]] = j;

            g[j].push_back(fx);
            g[j].push_back(fy);

            ++j;
        }
    }

    constexpr int limit = 21;
    auto stjump = std::vector(n << 1, std::vector<int>(limit));
    std::vector<int> deep(n << 1, 0), size(n << 1);
    ranges::fill(size.begin(), size.begin() + n, 1);

    for (int i = 0; i < (n << 1); ++i)
    {
        if (i != father[i])
        {
            continue;
        }

        [&](this auto &&dfs, int u, int f) -> void
        {
            deep[u] = deep[f] + 1;
            stjump[u][0] = f;

            for (int p = 1; p < limit; ++p)
            {
                stjump[u][p] = stjump[stjump[u][p - 1]][p - 1];
            }

            for (auto &v: g[u])
            {
                dfs(v, u);

                size[u] += size[v];
            }
        } (i, i);
    }

    int lim = 0;
    auto query = [&](int x)
    {
        for (int p = limit - 1; p >= 0; --p)
        {
            if (w[stjump[x][p]] >= lim)
            {
                x = stjump[x][p];
            }
        }

        return size[x];
    };

    std::stack<std::array<int, 2>> sta;
    while (q--)
    {
        int op;
        std::cin >> op;

        if (op == 1)
        {
            std::cin >> lim;

            while (!sta.empty())
            {
                auto [x, y] = sta.top();
                sta.pop();

                if (eton[x] != -1)
                {
                    w[eton[x]] = y;
                }
            }
        }
        else if (op == 2)
        {
            int x;
            std::cin >> x;
            --x;

            std::cout << query(x) << "\n";
        }
        else
        {
            int x, y;
            std::cin >> x >> y;
            --x;

            sta.push({x, y});
        }
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
