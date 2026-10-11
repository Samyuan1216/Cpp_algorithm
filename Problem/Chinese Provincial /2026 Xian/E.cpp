#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

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
    int n, x;
    std::cin >> n >> x;

    std::map<int, int> s;
    for (int i = 0, a; i < n; ++i)
    {
        std::cin >> a;

        ++s[a];
    }

    i64 ans = 0;
    for (auto &[key, val]: s)
    {
        if (val <= x)
        {
            ans += val;
        }
    }

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
