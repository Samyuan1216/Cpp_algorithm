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
    int n;
    std::cin >> n;

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;

        x *= 2;
    }

    int ans = 0;
    [&](this auto &&self, int i, i64 idx, int cnt) -> void
    {
        if (i == n)
        {
            ans = std::max(ans, cnt);
            return;
        }

        self(i + 1, idx + arr[i], (std::signbit(idx) == std::signbit(idx + arr[i])? cnt: cnt + 1));
        self(i + 1, idx - arr[i], (std::signbit(idx) == std::signbit(idx - arr[i])? cnt: cnt + 1));
    } (0, 1, 0);

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
