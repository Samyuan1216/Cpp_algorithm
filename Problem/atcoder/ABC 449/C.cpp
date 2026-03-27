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
    int n, l, r;
    std::cin >> n >> l >> r;
    ++r;

    auto str = std::string();
    std::cin >> str;

    auto cnt = std::array<int, 26>();
    i64 ans = 0;
    for (int i = 0; i < n; ++i)
    {
        if (i >= l)
        {
            ++cnt[str[i - l] - 'a'];
        }

        if (i >= r)
        {
            --cnt[str[i - r] - 'a'];
        }

        ans += cnt[str[i] - 'a'];
    }

    std::cout << ans << "\n";
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
