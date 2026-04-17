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

    std::vector<int> cap(k);
    for (auto &x: cap)
    {
        std::cin >> x;
    }

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;

        --x;
    }

    std::vector<int> ord(n);
    ranges::iota(ord, 0);
    ranges::sort(ord, [&](auto &a, auto &b)
    {
        return arr[a] > arr[b];
    });

    int sum = 0;
    std::vector<int> cnt(n);
    for (int i = 0; i < n; ++i)
    {
        cnt[i] = k - arr[ord[i]];
        sum += cnt[i];
    }

    if (sum > 1000)
    {
        std::cout << -1 << "\n";
        return;
    }

    std::cout << sum << "\n";
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < cnt[i]; ++j)
        {
            std::cout << ord[i] + 1 << " ";
        }
    }
    std::cout << "\n";
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
