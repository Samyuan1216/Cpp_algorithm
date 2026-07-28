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
    int m, d;
    std::string str;
    std::cin >> m >> d >> str;

    std::vector<int> arr(m);
    for (int i = 0; i < m; ++i)
    {
        if (str[i] == 'G')
        {
            ++arr[std::max(0, i - d)];
            if (i + d + 1 < m)
            {
                --arr[i + d + 1];
            }
        }
    }

    for (int i = 1; i < m; ++i)
    {
        arr[i] += arr[i - 1];
    }

    std::cout << ranges::count(arr, 0) << "\n";
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
