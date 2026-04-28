#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

template<typename T>
using lim = std::numeric_limits<T>;

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

    std::vector<int> status(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> status[i];
    }

    std::vector<std::vector<int>> g(n);
    for (int v = 1, u; v < n; ++v)
    {
        std::cin >> u;
        --u;

        g[u].push_back(v);
    }

    int cnt = 0;
    int ans = [&](this auto &&dfs, int u) -> int
    {
        bool visited = false;
        int cntu = 0;

        for (auto &v: g[u])
        {
            visited = true;
            int cntv = dfs(v);

            if (status[u] == 1)
            {
                cntu = (cntu == 0? cntv: std::min(cntu, cntv));
            }
            else
            {
                cntu += cntv;
            }
        }

        if (!visited)
        {
            ++cnt;
            cntu = 1;
        }

        return cntu;
    } (0);

    std::cout << cnt - ans + 1 << "\n";
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
