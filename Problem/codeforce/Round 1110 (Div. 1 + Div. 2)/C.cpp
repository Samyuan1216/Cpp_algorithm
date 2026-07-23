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
    int n, k;
    std::cin >> n >> k;

    k ^= n;
    if (std::bit_floor(unsigned(k)) > unsigned(n - 1))
    {
        std::cout << "NO\n";
        return;
    }

    int cnt = std::popcount(unsigned(k));
    std::vector<int> ans(n);
    bool visited[n] = {};

    for (int i = n - cnt; i < n; ++i)
    {
        ans[i] = k & -k;
        visited[k & -k] = true;
        k -= k & -k;
    }

    visited[0] = true;
    for (int i = 0, j = 0; i < n - cnt - 1; ++i)
    {
        while (j < n && visited[j])
        {
            ++j;
        }

        ans[i] = j;
        visited[j] = true;
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
