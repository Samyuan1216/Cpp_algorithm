#include <bits/stdc++.h>
#include <bits/extc++.h>
namespace ranges = std::ranges;
namespace views = std::views;

using i64 = int64_t;
using i128 = __int128;
using u64 = uint64_t;
using u128 = unsigned __int128;
using f64 = double;
using f128 = long double;

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
    std::vector<int> cnt(1000000);

    int n;
    std::cin >> n;

    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;
        cnt[x - 1]++;
    }

    for (int i = cnt.size() - 2; i >= 0; --i)
    {
        cnt[i] += cnt[i + 1];
    }

    int i = 0;
    while (cnt[i] > 0)
    {
        cnt[i + 1] += cnt[i] / 10;
        cnt[i++] %= 10;
    }

    while (--i >= 0)
    {
        std::cout << cnt[i];
    }
    std::cout << "\n";
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
