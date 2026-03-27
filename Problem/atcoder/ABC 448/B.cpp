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

    auto C = std::vector<int>(m + 1);
    for (int i = 1; i <= m; ++i)
    {
        std::cin >> C[i];
    }

    int ans = 0;
    for (int i = 1, a, b; i <= n; ++i)
    {
        std::cin >> a >> b;

        int add = (C[a] < b? C[a]: b);
        ans += add;
        C[a] -= add;
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
