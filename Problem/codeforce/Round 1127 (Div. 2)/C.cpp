#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

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
    i64 n;
    std::cin >> n;

    auto check = [&](i64 mid) -> bool
    {
        i64 cnt = mid, tmp = mid;
        while (--tmp)
        {
            cnt += tmp * (mid / tmp);
        }

        return cnt >= n;
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

    i64 ans = *find(1ll, n);
    std::cout << ans << "\n";

    std::vector<int> packet;
    i64 tmp = ans;

    while (n > 0)
    {
        int cnt = ans / tmp;
        for (int j = 0; j < cnt && n > 0; ++j)
        {
            packet.push_back(std::min(tmp, n));
            n -= tmp;
        }

        --tmp;
    }

    for (int i = 1; auto &x: packet)
    {
        while (x--)
        {
            std::cout << i << " ";
        }

        ++i;
    }

    std::cout << "\n";
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