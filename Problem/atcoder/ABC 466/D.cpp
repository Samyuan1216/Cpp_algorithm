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

    std::vector<int> r(m), c(m), lr(n + 1, -1), lc(n + 1, -1);
    for (int i = 0; i < m; ++i)
    {
        std::cin >> r[i] >> c[i];

        lr[r[i]] = lc[c[i]] = i;
    }

    int ans = 0;
    for (int i = 0; i < m; ++i)
    {
        if (lr[r[i]] == i && lc[c[i]] == i)
        {
            ++ans;
        }
    }

    std::cout << ans << "\n";
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
