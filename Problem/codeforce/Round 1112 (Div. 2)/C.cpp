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

    std::vector<std::array<int, 4>> arr(n);
    for (auto &[l, r, u, v]: arr)
    {
        std::cin >> l >> r >> u >> v;
    }

    auto check = [&](int aim) -> bool
    {
        int len = 0;
        for (int i = 0, l = 1, r; i < n; ++i)
        {
            r = aim - l + 1;
            if ((l < arr[i][0] || l > arr[i][1]) && (r < arr[i][2] || r > arr[i][3]))
            {
                ++len;
                ++l;
            }

            if (len == aim)
            {
                break;
            }
        }

        return len == aim;
    };

    int ans = 0;
    for (int len = 1; len <= n; ++len)
    {
        if (check(len))
        {
            ans = len;
        }
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
