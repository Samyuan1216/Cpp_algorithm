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
    int m;
    std::cin >> m;

    auto compute = [](int l, int r, int aim) -> std::string
    {
        auto ans = std::string{"RED"};
        while (l < r)
        {
            int mid = std::midpoint(l, r);
            if (aim <= mid)
            {
                r = mid;
            }
            else
            {
                ans = (ans == "RED"? "BLACK": "RED");
                l = mid + 1;
            }
        }

        return ans;
    };

    while (m--)
    {
        int n, k;
        std::cin >> n >> k;
        std::cout << compute(1, std::pow(2, n - 1), k) << "\n";
    }
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
