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

    std::vector<i64> arr(n);
    for (auto &x: arr)
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

    struct Info
    {
        i64 sum = 0, no = 0, max = 0;
        int deep = 0, v = -1, subdeep = 0, subv = -1;
    };

    std::vector<i64> ans(n);
    std::vector<Info> info(n);

    [&](this auto &&dfs, int u, int f) -> void
    {
        Info res{arr[u]};
        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            dfs(v, u);

            res.no += info[v].no + info[v].sum;
            res.sum += info[v].sum;
            if (info[v].deep + 1 >= res.deep)
            {
                res.subdeep = res.deep;
                res.subv = res.v;
                res.deep = info[v].deep + 1;
                res.v = v;
            }
            else if (info[v].deep + 1 > res.subdeep)
            {
                res.subdeep = info[v].deep + 1;
                res.subv = v;
            }
        }

        res.max = res.no;
        if (res.subv == -1)
        {
            if (res.v != -1)
            {
                res.max = std::max(res.max, res.no - info[res.v].no + info[res.v].max);
            }

            info[u] = res;
            ans[u] = res.max;
            return;
        }

        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            res.max = std::max({res.max, res.no - info[v].no + info[v].max, res.no + (v != res.v? res.deep: res.subdeep) * info[v].sum});
        }

        info[u] = res;
        ans[u] = res.max;
    } (0, -1);

    for (int i = 0; i < n; ++i)
    {
        std::cout << ans[i] << " \n"[i == n - 1];
    }
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
