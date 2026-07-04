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

    std::vector<int> num(n + 1);

    std::vector<int> a(n);
    for (auto &x: a)
    {
        std::cin >> x;

        ++num[x];
    }

    std::vector<int> b(n);
    for (auto &x: b)
    {
        std::cin >> x;

        ++num[x];
    }

    for (auto &x: num)
    {
        if (x & 1)
        {
            std::cout << -1 << "\n";
            return;
        }
    }

    std::vector<int> head(n + 1, -1), next(n << 1, -1), to(n << 1, -1);
    int cnt = 0;

    auto add_edge = [&](int u, int v) -> void
    {
        next[cnt] = head[u];
        to[cnt] = v;
        head[u] = cnt++;
    };

    std::vector<int> degree(n + 1);
    for (int i = 0; i < n; ++i)
    {
        add_edge(a[i], b[i]);
        add_edge(b[i], a[i]);

        ++degree[a[i]], ++degree[b[i]];
    }

    auto cur = head;
    std::vector<int> ans;
    std::vector<bool> visited_node(n + 1), visited_edge(n);

    for (int i = 1; i <= n; ++i)
    {
        if (visited_node[i])
        {
            continue;
        }

        [&](this auto &&dfs, int u) -> void
        {
            visited_node[u] = true;
            for (int ei = cur[u]; ei != -1; ei = cur[u])
            {
                cur[u] = next[ei];
                if (!visited_edge[ei >> 1])
                {
                    visited_edge[ei >> 1] = true;
                    dfs(to[ei]);

                    if (ei & 1)
                    {
                        ans.push_back((ei >> 1) + 1);
                    }
                }
            }
        } (i);
    }

    std::cout << std::ssize(ans) << "\n";
    for (auto &x: ans)
    {
        std::cout << x << " ";
    }
    std::cout << "\n";
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
