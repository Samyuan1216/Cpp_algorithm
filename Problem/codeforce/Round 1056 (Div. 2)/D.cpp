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
    int n;
    std::cin >> n;

    for (int len = 1; len < n; ++len)
    {
        for (int i = 1; i <= n; ++i)
        {
            std::cout << i << " " << (i + len - 1) % n + 1 << std::endl;

            int x;
            std::cin >> x;

            if (x == -1 || x == 1)
            {
                return;
            }
        }
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
