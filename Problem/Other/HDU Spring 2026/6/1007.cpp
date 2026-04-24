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
    int n, m;
    std::cin >> n >> m;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    {
        std::vector<bool> visited(m);
        for (auto &x: arr)
        {
            if (x >= 1 && x <= m)
            {
                visited[x - 1] = true;
            }
        }

        for (int i = 0; i < m; ++i)
        {
            if (!visited[i])
            {
                std::cout << -1 << "\n";
                return;
            }
        }
    }

    std::vector<int> mp(m + 1, 0);
    int cnt = 0, ans = lim<int>::max();

    for (int i = 0, j = 0; j < n; ++j)
    {
        if (arr[j] >= 1 && arr[j] <= m)
        {
            if (mp[arr[j]] == 0)
            {
                ++cnt;
            }

            ++mp[arr[j]];
        }

        while (i <= j && (arr[i] > m || mp[arr[i]] > 1))
        {
            if (arr[i] >= 1 && arr[i] <= m)
            {
                --mp[arr[i]];
            }

            ++i;
        }

        if (cnt == m) 
        {
            ans = std::min(ans, j - i + 1);
        }
    }

    std::cout << ans - m << "\n";
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
