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
    int n, k;
    std::cin >> n >> k;

    std::string s, t;
    std::cin >> s >> t;

    bool check = true;
    for (int i = std::max(0, n - k); i < std::min(n, k); ++i)
    {
        if (s[i] != t[i])
        {
            check = false;
            break;
        }
    }

    ranges::sort(s);
    ranges::sort(t);

    std::cout << (check && s == t? "YES\n": "NO\n");
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
