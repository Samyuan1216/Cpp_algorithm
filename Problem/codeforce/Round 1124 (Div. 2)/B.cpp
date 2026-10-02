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

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    auto compute = [&](i64 x) -> i64
    {
        int res = 0;
        while (x > 0)
        {
            res += (x % 10) * (x % 10);
            x /= 10;
        }

        return res;
    };

    std::array<std::map<i64, int>, 1010> has{};
    i64 ans = 0;

    for (auto &x: arr)
    {
        int tmp = x;
        for (int i = 0, cnt = 0; i < 1010; ++i)
        {
            if (has[i].contains(tmp))
            {
                ans += has[i][tmp] - cnt;
                cnt += has[i][tmp] - cnt;
                ++has[i][tmp];
            }
            else
            {
                ++has[i][tmp];
            }

            tmp = compute(tmp);
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
