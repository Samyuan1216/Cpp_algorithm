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
    int n, d;
    std::cin >> n >> d;

    std::vector<int> s(n), t(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> s[i] >> t[i];
        --s[i], --t[i];
    }

    int max = *ranges::max_element(t);
    std::vector<int> diff(max + 1);

    for (int i = 0, l, r; i < n; ++i)
    {
        l = s[i], r = t[i] - d;
        if (l <= r)
        {
            diff[l] += 1, diff[r + 1] -= 1;
        }
    }

    for (int i = 1; i <= max; ++i)
    {
        diff[i] += diff[i - 1];
    }

    i64 ans = 0;
    for (int x = 0; x <= max; ++x)
    {
        i64 c = diff[x];
        ans += c * (c - 1) / 2;
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
