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

    std::vector<std::vector<int>> g(n);
    std::vector<int> color(n);
    int s = 0, m = 0;

    for (int i = 0, c, p; i < n; ++i)
    {
        std::cin >> c >> p;
        --p;

        color[i] = c;
        m = std::max(m, c);

        if (p == -1)
        {
            s = i;
        }
        else
        {
            g[p].push_back(i);
        }
    }

    std::vector<int> size(n, 1), son(n, -1);
    [&](this auto &&dfs, int u) -> void
    {
        for (auto &v: g[u])
        {
            dfs(v);

            size[u] += size[v];
            if (son[u] == -1 || size[son[u]] < size[v])
            {
                son[u] = v;
            }
        }
    } (s);

    std::vector<int> cnt(m + 1);
    int diff = 0, max = 0, num = 0;

    auto effect = [&](this auto &&dfs, int u) -> void
    {
        if (++cnt[color[u]] == 1)
        {
            ++num;
            if (max > 1)
            {
                ++diff;
            }
        }
        else if (cnt[color[u]] == max)
        {
            --diff;
        }
        else if (cnt[color[u]] > max)
        {
            max = cnt[color[u]];
            diff = num - 1;
        }

        for (auto &v: g[u])
        {
            dfs(v);
        }
    };

    auto cancel = [&](this auto &&dfs, int u) -> void
    {
        cnt[color[u]] = 0;
        diff = 0, max = 0, num = 0;

        for (auto &v: g[u])
        {
            dfs(v);
        }
    };

    int ans = 0;
    [&](this auto &&dfs, int u, int keep) -> void
    {
        for (auto &v: g[u])
        {
            if (v == son[u])
            {
                continue;
            }

            dfs(v, 0);
        }

        if (son[u] != -1)
        {
            dfs(son[u], 1);
        }

        for (auto &v: g[u])
        {
            if (v == son[u])
            {
                continue;
            }

            effect(v);
        }

        if (++cnt[color[u]] == 1)
        {
            ++num;
            if (max > 1)
            {
                ++diff;
            }
        }
        else if (cnt[color[u]] == max)
        {
            --diff;
        }
        else if (cnt[color[u]] > max)
        {
            max = cnt[color[u]];
            diff = num - 1;
        }

        if (diff == 0)
        {
            ++ans;
        }

        if (keep == 0)
        {
            cancel(u);
        }
    } (s, 0);

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
