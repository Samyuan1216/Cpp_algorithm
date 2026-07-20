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
    int n, k, m;
    std::cin >> n >> k >> m;

    if (k > m)
    {
        std::cout << "NO\n";
        return;
    }

    std::vector<int> arr(n, 1);
    arr[0] = m - k + 1;

    std::cout << "YES\n";
    for (int i = 0; i < n; ++i)
    {
        std::cout << arr[i] << " \n"[i == n - 1];
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
