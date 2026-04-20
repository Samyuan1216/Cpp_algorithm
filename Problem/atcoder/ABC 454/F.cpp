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
    int n, m;
    std::cin >> n >> m;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    if (n == 1)
    {
        std::cout << 0 << "\n";
        return;
    }

    std::vector<int> arr1(n / 2);
    for (int i = 0; i < n / 2; ++i)
    {
        arr1[i] = (m + (arr[n - i - 1] - arr[i])) % m;
    }

    std::vector<int> arr2(n / 2);
    for (int i = 0; i < n / 2; ++i)
    {
        arr2[i] = (m - arr1[i]) % m;
    }

    n /= 2;

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
