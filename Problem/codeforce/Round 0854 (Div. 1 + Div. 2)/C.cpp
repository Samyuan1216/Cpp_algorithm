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
    std::string str;
    std::cin >> str;

    std::array<int, 26> cnt{};
    for (auto &c: str)
    {
        ++cnt[c - 'a'];
    }

    std::string left, right;
    for (int i = 0; i < 26; ++i)
    {
        while (cnt[i] >= 2)
        {
            left += i + 'a';
            right += i + 'a';
            cnt[i] -= 2;
        }

        if (cnt[i] == 0)
        {
            continue;
        }

        cnt[i] = 0;

        int kinds = 0, next = -1;
        for (int j = i + 1; j < 26; ++j)
        {
            if (cnt[j] > 0)
            {
                ++kinds;
                next = j;
            }
        }

        if (kinds == 0)
        {
            left += i + 'a';
        }
        else if (kinds == 1)
        {
            left += std::string((cnt[next] + 1) / 2, next + 'a');
            left += i + 'a';
            left += std::string(cnt[next] / 2, next + 'a');
        }
        else
        {
            for (int j = i + 1; j < 26; ++j)
            {
                left += std::string(cnt[j], j + 'a');
            }

            left += i + 'a';
        }

        break;
    }

    ranges::reverse(right);
    std::cout << left + right << "\n";
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
