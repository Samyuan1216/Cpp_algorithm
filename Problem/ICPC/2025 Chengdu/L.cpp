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

    std::vector<int> a(n);
    for (auto &x: a)
    {
        std::cin >> x;
    }

    std::vector<int> b(n);
    for (auto &x: b)
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

    std::vector<int> father(n), size(n, 1), son(n, -1);
    [&](this auto &&dfs, int u, int f) -> void
    {
        father[u] = f;
        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            dfs(v, u);

            size[u] += size[v];
            if (son[u] == -1 || size[son[u]] < size[v])
            {
                son[u] = v;
            }
        }
    } (0, 0);

    std::vector<int> acnt(n + 1), bcnt(n + 1);
    int s = 0;

    auto effect = [&](this auto &&dfs, int u) -> void
    {
        if (a[u] != 0)
        {
            s -= std::max(acnt[a[u]], bcnt[a[u]]);
            ++acnt[a[u]];
            s += std::max(acnt[a[u]], bcnt[a[u]]);
        }

        if (b[u] != 0)
        {
            s -= std::max(acnt[b[u]], bcnt[b[u]]);
            ++bcnt[b[u]];
            s += std::max(acnt[b[u]], bcnt[b[u]]);
        }

        for (auto &v: g[u])
        {
            if (v == father[u])
            {
                continue;
            }

            dfs(v);
        }
    };

    auto cancel = [&](this auto &&dfs, int u) -> void
    {
        if (a[u] != 0)
        {
            s -= std::max(acnt[a[u]], bcnt[a[u]]);
            --acnt[a[u]];
            s += std::max(acnt[a[u]], bcnt[a[u]]);
        }

        if (b[u] != 0)
        {
            s -= std::max(acnt[b[u]], bcnt[b[u]]);
            --bcnt[b[u]];
            s += std::max(acnt[b[u]], bcnt[b[u]]);
        }

        for (auto &v: g[u])
        {
            if (v == father[u])
            {
                continue;
            }

            dfs(v);
        }
    };

    std::string ans(n, '0');
    [&](this auto &&dfs, int u, int keep) -> void
    {
        for (auto &v: g[u])
        {
            if (v == father[u] || v == son[u])
            {
                continue;
            }

            dfs(v, 0);
        }

        if (son[u] != -1)
        {
            dfs(son[u], 1);
        }

        if (a[u] != 0)
        {
            s -= std::max(acnt[a[u]], bcnt[a[u]]);
            ++acnt[a[u]];
            s += std::max(acnt[a[u]], bcnt[a[u]]);
        }

        if (b[u] != 0)
        {
            s -= std::max(acnt[b[u]], bcnt[b[u]]);
            ++bcnt[b[u]];
            s += std::max(acnt[b[u]], bcnt[b[u]]);
        }

        for (auto &v: g[u])
        {
            if (v == father[u] || v == son[u])
            {
                continue;
            }

            effect(v);
        }

        if (s <= size[u])
        {
            ans[u] = '1';
        }

        if (keep == 0)
        {
            cancel(u);
        }
    } (0, 0);

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
