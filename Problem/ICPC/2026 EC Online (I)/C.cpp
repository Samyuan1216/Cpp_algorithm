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

    std::vector<std::vector<int>> g(n);
    std::vector<int> in(n);

    while (m--)
    {
        int l, r;
        std::cin >> l >> r;

        std::vector<int> p;
        for (int i = l, x; i <= r; ++i)
        {
            std::cin >> x;
            --x;

            p.push_back(x);
        }

        for (int i = 0; i < std::ssize(p) - 1; ++i)
        {
            g[p[i]].push_back(p[i + 1]);
            ++in[p[i + 1]];
        }
    }

    std::priority_queue<int, std::vector<int>, std::greater<>> heap;
    for (int i = 0; i < n; ++i)
    {
        if (in[i] == 0)
        {
            heap.push(i);
        }
    }

    std::vector<int> ans(n);
    int num = 0;

    while (!heap.empty())
    {
        int u = heap.top();
        heap.pop();

        ans[u] = ++num;
        for (auto &v: g[u])
        {
            if (--in[v] == 0)
            {
                heap.push(v);
            }
        }
    }

    if (num != n)
    {
        std::cout << -1 << "\n";
        return;
    }

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
