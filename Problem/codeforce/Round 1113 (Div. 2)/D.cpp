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
    int n, q;
    std::cin >> n >> q;

    std::string s, t;
    std::cin >> s >> t;

    std::vector<int> p(n + 1), d(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        p[i] = p[i - 1] + (s[i - 1] == t[i - 1]? 1: 0);
        d[i] = d[i - 1] + (s[i - 1] - t[i - 1]);
    }

    while (q--)
    {
        int l, r;
        std::cin >> l >> r;
        std::cout << (p[r] - p[l - 1] >= std::abs(d[r] - d[l - 1])? "YES\n": "NO\n");
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
