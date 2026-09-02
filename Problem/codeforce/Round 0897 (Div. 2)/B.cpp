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
    std::string str;
    std::cin >> n >> str;

    int num1 = 0, num2 = 0, num3 = 0;
    for (int i = 0, j = n - 1; i <= j; ++i, --j)
    {
        if (str[i] != str[j])
        {
            ++num1;
        }
        else
        {
            if (i < j)
            {
                ++num2;
            }
            else
            {
                ++num3;
            }
        }
    }

    std::string ans(n + 1, '0');
    for (int i = num1; i <= n && num2 >= 0; i += 2, --num2)
    {
        ans[i] = '1';
        if (i + num3 <= n)
        {
            ans[i + num3] = '1';
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
