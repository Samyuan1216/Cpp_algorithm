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

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    bool status = true;
    [&](this auto &&dfs, int u) -> std::array<int, 2>
    {
        if (!status)
        {
            return {0, 0};
        }

        if (g[u].empty())
        {
            return {arr[u], arr[u]};
        }

        std::vector<std::array<int, 2>> child;
        int min = 2e9, max = -2e9;

        for (auto &v: g[u])
        {
            auto infov = dfs(v);
            if (!status)
            {
                return {0, 0};
            }

            child.push_back(infov);
            min = std::min(min, infov[0]);
            max = std::max(max, infov[1]);
        }

        int m = std::ssize(child);
        if (m == 1)
        {
            return {min, max};
        }

        child.insert(child.end(), child.begin(), child.end());

        bool ok = false;
        for (int i = 0, cur = 0; i < 2 * m - 1; ++i)
        {
            if (child[i][1] < child[i + 1][0])
            {
                ++cur;
            }
            else
            {
                cur = 0;
            }

            if (cur >= m - 1)
            {
                ok = true;
                break;
            }
        }

        if (!ok)
        {
            status = false;
            return {0, 0};
        }

        return {min, max};
    } (0);

    std::cout << (status? "YES\n": "NO\n");
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
