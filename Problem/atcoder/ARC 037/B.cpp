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

    std::vector<bool> vis(n);
    int ans = 0;

    for (int i = 0; i < n; ++i)
    {
        if (vis[i])
        {
            continue;
        }

        int cntn = 0, cntm = 0;
        [&](this auto &&self, int u) -> void
        {
            ++cntn;
            vis[u] = true;

            for (auto &v: g[u])
            {
                ++cntm;
                if (vis[v])
                {
                    continue;
                }

                self(v);
            }
        } (i);

        if (cntm / 2 == cntn - 1)
        {
            ++ans;
        }
    }

    std::cout << ans << "\n";
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
