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
    int n, m;
    std::cin >> n >> m;

    i64 num = 1;
    for (int i = 0; i < m + 1; ++i)
    {
        num *= 2;
    }

    --num;

    i64 ans = 0;
    for (int i = 0; i < n; ++i)
    {
        i64 x;
        std::cin >> x;

        ans ^= x % num;
    }

    std::cout << (ans != 0? "First\n": "Second\n");
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
