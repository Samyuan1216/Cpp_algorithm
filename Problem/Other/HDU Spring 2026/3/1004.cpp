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

    auto degree = std::vector<int>(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 2 * i; j <= n; j += i)
        {
            ++degree[i], ++degree[j];
        }
    }

    ranges::sort(degree, std::greater<>());
    std::cout << degree[k - 1] << "\n";
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
