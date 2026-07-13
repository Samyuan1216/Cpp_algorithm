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
    std::string str;
    std::cin >> n >> str;

    std::array<i64, 3> cnt{1, 0, 0};
    i64 ans = 0;

    for (int i = 0, cur = 0, y = 0; i < n; ++i)
    {
        if (str[i] == '1')
        {
            cur = (cur + 1) % 3;
        }
        else
        {
            cur = (cur + 2) % 3;
        }

        if (i > 0 && str[i] != str[i - 1])
        {
            ++y;
        }
        else
        {
            y = 1;
        }

        ans += (i + 1) - cnt[cur];
        ans -= (y - 1) / 2;
        ++cnt[cur];
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
