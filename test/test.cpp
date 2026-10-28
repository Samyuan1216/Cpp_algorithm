#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

void solve()
{
    int x;
    std::cin >> x;
    std::cout << 2 * x << "\n";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    // std::cin >> t;
    while (t--)
    {
        solve();
    }
}