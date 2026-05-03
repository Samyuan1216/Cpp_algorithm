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

    std::vector<std::vector<int>> g(n);
    for (int i = 0, u, v; i < m; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    int w;
    std::cin >> w;

    std::vector<std::string> holiday(n);
    for (auto &str: holiday)
    {
        std::cin >> str;
    }

    auto g2 = std::vector(n, std::vector(w, std::vector<std::array<int, 2>>()));
    for (int u = 0; u < n; ++u)
    {
        for (int d = 0; d < w; ++d)
        {
            if (holiday[u][d] == 'x')
            {
                continue;
            }

            int nd = (d + 1) % w;
            if (holiday[u][nd] == 'o')
            {
                g2[u][d].push_back({u, nd});
            }

            for (auto &v: g[u])
            {
                if (holiday[v][nd] == 'x')
                {
                    continue;
                }

                g2[u][d].push_back({v, nd});
            }
        }
    }

    auto color = std::vector(n, std::vector<int>(w));
    bool status = false;

    for (int i = 0; i < n && !status; ++i)
    {
        if (color[i][0] != 0 || holiday[i][0] == 'x')
        {
            continue;
        }

        status = [&](this auto &&dfs, int u, int uw) -> bool
        {
            color[u][uw] = 1;
            for (auto &[v, vw]: g2[u][uw])
            {
                if (color[v][vw] == 2)
                {
                    continue;
                }

                if (color[v][vw] == 1 || dfs(v, vw))
                {
                    return true;
                }
            }

            color[u][uw] = 2;
            return false;
        } (i, 0);
    }

    std::cout << (status? "Yes\n": "No\n");
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
