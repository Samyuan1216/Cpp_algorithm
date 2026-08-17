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
    for (int i = 1, p; i < n; ++i)
    {
        std::cin >> p;
        --p;

        g[p].push_back(i);
    }

    int m;
    std::cin >> m;

    std::vector<bool> dams(n);
    for (int i = 0, a; i < m; ++i)
    {
        std::cin >> a;
        --a;

        dams[a] = true;
    }

    std::vector<int> cnt(n);
    [&](this auto &&self, int u) -> void
    {
        if (dams[u])
        {
            cnt[u] = 1;
        }

        for (auto &v: g[u])
        {
            self(v);

            cnt[u] += cnt[v];
        }
    } (0);

    std::vector<int> ans;
    [&](this auto &&self, int u) -> void
    {
        int num = 0;
        for (auto &v: g[u])
        {
            if (cnt[v] > 0)
            {
                ++num;
            }
        }

        if (!dams[u])
        {
            --num;
        }

        for (auto &v: g[u])
        {
            if (cnt[v] > 0 && (num-- > 0))
            {
                ans.push_back(v);
            }
        }

        for (auto &v: g[u])
        {
            if (cnt[v] > 1)
            {
                self(v);
            }
        }
    } (0);
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
