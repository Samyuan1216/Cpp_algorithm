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

    std::vector<i64> e, o;
    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;

        (i & 1? o.push_back(x): e.push_back(x));
    }

    auto compute = [&](int i) -> i64
    {
        i64 sum = 0, num = 0;
        for (int j = 0; j < std::ssize(o) && i < std::ssize(e); ++i, ++j)
        {
            num = std::max(0ll, num + o[j] - e[i]);
            sum = std::max(sum, num);
        }

        return sum;
    };

    i64 ans = 0;
    for (auto &x: e)
    {
        ans += x;
    }

    std::cout << ans + std::max(compute(0), compute(1)) << "\n";
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
