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

    std::vector<int> status(n);
    std::vector<std::array<int, 3>> query;

    for (int i = 0, op, l, r; i < m; ++i)
    {
        std::cin >> op >> l >> r;
        --l, --r;

        if (l == r)
        {
            status[l] = op;
        }
        else
        {
            query.push_back({op, l, r});
        }
    }

    std::vector<std::vector<int>> g(n);
    std::vector<int> in(n);

    for (auto &[op, i, j]: query)
    {
        if (status[i] == status[j] && status[i] != op)
        {
            std::cout << "NO\n";
            return;
        }

        if (status[i] != status[j])
        {
            if (status[i] == op)
            {
                g[j].push_back(i);
                ++in[i];
            }
            else
            {
                g[i].push_back(j);
                ++in[j];
            }
        }
    }

    std::vector<int> dp(n, 1);
    std::queue<int> q;

    for (int i = 0; i < n; ++i)
    {
        if (in[i] == 0)
        {
            q.push(i);
        }
    }

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto &v: g[u])
        {
            dp[v] = std::max(dp[v], dp[u] + 1);
            if (--in[v] == 0)
            {
                q.push(v);
            }
        }
    }

    if (ranges::count(in, 0) < n)
    {
        std::cout << "NO\n";
        return;
    }

    for (int i = 0; i < n; ++i)
    {
        dp[i] *= (status[i] == 1? 1: -1);
    }

    std::cout << "YES\n";
    for (int i = 0; i < n; ++i)
    {
        std::cout << dp[i] << " \n"[i == n - 1];
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
