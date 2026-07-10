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

    std::vector<int> arr(n);
    int sum = 0;

    for (auto &x: arr)
    {
        std::cin >> x;

        sum ^= x;
    }

    if (n == 1)
    {
        std::cout << 0 << "\n";
        return;
    }
    else if (sum == 0)
    {
        std::cout << 1 << "\n";
        return;
    }

    int ans = 0;
    for (auto &x: arr)
    {
        int t = sum ^ x;
        if (t < x)
        {
            ++ans;
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
