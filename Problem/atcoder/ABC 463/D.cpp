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
    int n, k;
    std::cin >> n >> k;

    std::vector<std::array<int, 2>> arr(n);
    for (auto &[r, l]: arr)
    {
        std::cin >> l >> r;
    }

    ranges::sort(arr);

    auto check = [&](int mid) -> bool
    {
        int end = -1, cnt = 0;
        for (auto &[r, l]: arr)
        {
            if (end == -1 || l - end >= mid)
            {
                end = r;
                ++cnt;

                if (cnt == k)
                {
                    return true;
                }
            }
        }

        return false;
    };

    auto find = [&](auto l, auto r, bool find_first = true) -> std::optional<decltype(l)>
    {
        std::optional<decltype(l)> ans;
        while (l <= r)
        {
            auto mid = std::midpoint(l, r);
            if (check(mid))
            {
                ans = mid;
                find_first? (r = mid - 1): (l = mid + 1);
            }
            else
            {
                find_first? (l = mid + 1): (r = mid - 1);
            }
        }
    
        return ans;
    };

    auto ans = find(1, int(1e9), false);
    std::cout << (ans? *ans: -1) << "\n";
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
