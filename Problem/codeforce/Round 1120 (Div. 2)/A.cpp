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

    int cnt0 = 0, cnt1 = 0;
    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;

        ++(x == 0? cnt0: cnt1);
    }

    bool status = true;
    while (cnt0 > 0 && cnt1 > 0)
    {
        --(status? cnt0: cnt1);
        status = !status;
    }

    std::cout << (cnt1 > 0? "Bessie\n": "Elsie\n");
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
