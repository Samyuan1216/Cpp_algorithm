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

    std::vector<std::vector<std::array<int, 2>>> g(n);
    std::vector<int> d1(n), d2(n);

    for (int i = 0, op, l, r; i < m; ++i)
    {
        std::cin >> op >> l >> r;
        --l, --r;

        if (l == r)
        {
            g[l].push_back({l, op});
            if (op == 1)
            {
                ++d1[l];
            }
            else
            {
                ++d2[l];
            }
        }
        else
        {
            g[l].push_back({r, op});
            g[r].push_back({l, op});

            if (op == 1)
            {
                ++d1[l], ++d1[r];
            }
            else
            {
                ++d2[l], ++d2[r];
            }
        }
    }

    std::queue<int> q;
    bool in_q[n] = {};

    for (int i = 0; i < n; ++i)
    {
        if (d1[i] == 0 || d2[i] == 0)
        {
            q.push(i);
            in_q[i] = true;
        }
    }

    std::vector<int> ans(n);
    int cur = n, cnt = 0;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        if (d2[u] == 0)
        {
            ans[u] = cur;
        }
        else
        {
            ans[u] = -cur;
        }

        ++cnt, --cur;
        for (auto &[v, op]: g[u])
        {
            if (op == 1)
            {
                --d1[v];
            }
            else
            {
                --d2[v];
            }

            if (!in_q[v] && (d1[v] == 0 || d2[v] == 0))
            {
                q.push(v);
                in_q[v] = true;
            }
        }
    }

    if (cnt < n)
    {
        std::cout << "NO\n";
        return;
    }

    std::cout << "YES\n";
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
