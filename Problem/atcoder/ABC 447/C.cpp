#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = int64_t;

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
    std::string str1, str2;
    std::cin >> str1 >> str2;

    auto count = [&](std::string &str)
    {
        std::vector<int> counts;

        int cnt = 0;
        for (auto &c: str)
        {
            if (c == 'A')
            {
                ++cnt;
            }
            else
            {
                counts.push_back(cnt);
                cnt = 0;
            }
        }

        counts.push_back(cnt);
        return counts;
    };

    auto count1 = count(str1);
    std::erase(str1, 'A');

    auto count2 = count(str2);
    std::erase(str2, 'A');

    if (str1 != str2)
    {
        std::cout << "-1\n";
        return;
    }

    int ans = 0;
    for (int i = 0; i < std::ssize(count1); ++i)
    {
        ans += std::abs(count1[i] - count2[i]);
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
