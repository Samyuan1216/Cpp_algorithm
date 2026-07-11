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

    std::vector<int> size(m, -1);
    for (int i = 0, c, s; i < n; ++i)
    {
        std::cin >> c >> s;

        size[c - 1] = std::max(size[c - 1], s);
    }

    for (int i = 0; i < m; ++i)
    {
        std::cout << size[i] << " \n"[i == m - 1];
    }
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
