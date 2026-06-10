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

    std::vector<int> a(n);
    for (auto &x: a)
    {
        std::cin >> x;
    }

    std::vector<int> b(m);
    for (auto &x: b)
    {
        std::cin >> x;
    }

    ranges::sort(a, std::greater());
    ranges::sort(b, std::greater());

    int ans = 0;
    for (int i = 0, j = 0; i < n && j < m;)
    {
        if (a[i] * 2 >= b[j])
        {
            ++i, ++j, ++ans;
        }
        else
        {
            ++j;
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
