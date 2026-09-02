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
    int n;
    std::cin >> n;

    std::array<int, 101> cnt{};
    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;

        ++cnt[x];
    }

    int sum = 0;
    for (int i = 0; i <= 100; ++i)
    {
        if (cnt[i] & 1)
        {
            sum += i;
        }
    }

    std::cout << sum << "\n";
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
