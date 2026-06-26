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
    int n, m, l, s, t;
    std::cin >> n >> m >> l >> s >> t;

    std::vector<std::vector<std::array<int, 2>>> g(n);
    for (int i = 0, u, v, c; i < m; ++i)
    {
        std::cin >> u >> v >> c;
        --u, --v;

        g[u].push_back({v, c});
    }

    std::queue<std::array<int, 2>> q;
    q.push({0, 0});

    int level = 0;
    while (level < l && !q.empty())
    {
        int size = std::ssize(q);
        for (int i = 0; i < size; ++i)
        {
            auto [u, uc] = q.front();
            q.pop();

            for (auto &[v, vc]: g[u])
            {
                if (uc + vc > t)
                {
                    continue;
                }

                q.push({v, uc + vc});
            }
        }

        ++level;
    }

    bool visited[n + 1] = {};
    while (!q.empty())
    {
        auto [u, c] = q.front();
        q.pop();

        if (c >= s)
        {
            visited[u + 1] = true;
        }
    }

    if (level < l)
    {
        std::cout << "\n";
        return;
    }

    for (int i = 1; i <= n; ++i)
    {
        if (visited[i])
        {
            std::cout << i << " ";
        }
    }
    std::cout << "\n";
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
