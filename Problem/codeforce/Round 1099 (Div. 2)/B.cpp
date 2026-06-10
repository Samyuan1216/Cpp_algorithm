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

    i64 k = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        if (arr[i] > arr[i + 1])
        {
            k = std::max(k, arr[i] - arr[i + 1]);
        }
    }

    i64 prev = arr[0];
    for (int i = 1; i < n; ++i)
    {
        if (prev <= arr[i])
        {
            prev = arr[i];
            continue;
        }

        if (prev > arr[i] + k)
        {
            std::cout << "NO\n";
            return;
        }

        prev = arr[i] + k;
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
