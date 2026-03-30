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
    auto count_num = [](int num) -> std::array<int, 10>
    {
        auto cnt = std::array<int, 10>();
        while (num > 0)
        {
            ++cnt[num % 10];
            num /= 10;
        }

        return cnt;
    };

    int y = 2239, m = 9, d = 9, ans = 0;
    auto day_up = [&]() -> void
    {
        if (m == 2 && d == 28)
        {
            if (y % 400 == 0 || (y % 100 != 0 && y % 4 == 0))
            {
                ++d;
            }
            else
            {
                m = 3, d = 1;
            }
        }
        else if ((m == 2 && d == 29) || ((m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10) && d == 31) || ((m == 4 || m == 6 || m == 9 || m == 11) && d == 30))
        {
            ++m;
            d = 1;
        }
        else if (m == 12 && d == 31)
        {
            ++y;
            m = d = 1;
        }
        else
        {
            ++d;
        }
    };

    for (; !(y == 9876 && m == 1 && d == 2); day_up())
    {
        auto cnt = std::vector<int>(10);
        auto y_cnt = count_num(y), m_cnt = count_num(m), d_cnt = count_num(d);
        for (int i = 0; i <= 9; ++i)
        {
            cnt[i] = y_cnt[i] + m_cnt[i] + d_cnt[i];
        }

        std::erase(cnt, 0);
        auto [l, r] = ranges::unique(cnt);
        cnt.erase(l, r);

        if (std::ssize(cnt) == 1)
        {
            ++ans;
        }
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
