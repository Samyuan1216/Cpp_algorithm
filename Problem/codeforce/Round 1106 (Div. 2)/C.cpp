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

    int ans = 0;
    [&](this auto &&dfs, int u) -> int
    {
        ++ans;

        int max = 0, submax = 0;
        for (auto &v: g[u])
        {
            int h = dfs(v);
            if (h > max)
            {
                submax = max;
                max = h;
            }
            else if (h > submax)
            {
                submax = h;
            }
        }

        ans += submax;
        return max + 1;
    } (0);

    std::cout << ans << "\n";
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
