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

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    for (int i = 0; i < n - 1; ++i)
    {
        if (arr[i] < i + 1)
        {
            std::cout << "NO\n";
            return;
        }

        arr[i + 1] += arr[i] - (i + 1);
        arr[i] = i + 1;
    }

    if (arr[n - 1] < n)
    {
        std::cout << "NO\n";
        return;
    }

    std::cout << "YES\n";
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
