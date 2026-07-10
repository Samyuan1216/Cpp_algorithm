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
    int n;
    std::cin >> n;

    std::vector<i64> w(n);
    for (auto &x: w)
    {
        std::cin >> x;
    }

    std::vector<std::vector<int>> g(n);
    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    auto check = [&](i64 x) -> bool
    {
        if (x < 0)
        {
            return false;
        }

        i64 r = std::round(std::sqrt(x));
        return r * r == x;
    };

    std::vector<i64> size(n, 1);
    [&](this auto &&dfs, int u, int f) -> void
    {
        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            dfs(v, u);
            size[u] += size[v];
        }
    } (0, -1);

    i64 ans = 0;
    for (int u = 0; u < n; ++u)
    {
        if (!check(w[u]))
        {
            continue;
        }

        i64 sum = 0, pair = 0, tri = 0;
        for (auto &v: g[u])
        {
            i64 sizev = (size[v] < size[u]? size[v]: n - size[u]);
            tri += pair * sizev;
            pair += sum * sizev;
            sum += sizev;
        }

        ans += pair + tri;
    }

    std::cout << ans << "\n";
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
