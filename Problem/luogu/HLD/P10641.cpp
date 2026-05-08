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
    int n, k;
    std::cin >> n >> k;

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    std::vector<std::vector<int>> g(n);
    std::vector<bool> appear(n);

    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
        appear[v] = true;
    }

    int root = 0;
    for (int i = 0; i < n; ++i)
    {
        if (!appear[i])
        {
            root = i;
            break;
        }
    }

    std::vector<i64> money(n), son(n, -1);
    [&](this auto &&dfs, int u) -> void
    {
        money[u] = arr[u];
        for (auto &v: g[u])
        {
            dfs(v);

            if (son[u] == -1 || money[son[u]] < money[v])
            {
                money[u] -= (son[u] == -1? 0: money[son[u]]);
                money[u] += money[v];
                son[u] = v;
            }
        }
    } (root);

    std::vector<i64> top(n);
    [&](this auto &&dfs, int u, int t) -> void
    {
        top[u] = t;
        if (son[u] == -1)
        {
            return;
        }

        dfs(son[u], t);
        for (auto &v: g[u])
        {
            if (v == son[u])
            {
                continue;
            }

            dfs(v, v);
        }
    } (root, root);

    std::vector<i64> sorted;
    for (int i = 0; i < n; ++i)
    {
        if (i == top[i])
        {
            sorted.push_back(money[i]);
        }
    }

    ranges::sort(sorted, std::greater());

    i64 ans = 0;
    for (int i = 0; i < std::min(k, int(std::ssize(sorted))); ++i)
    {
        ans += sorted[i];
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
