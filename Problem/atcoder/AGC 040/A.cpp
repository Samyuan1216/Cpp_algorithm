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
    std::string str;
    std::cin >> str;

    int n = str.length();
    auto arr = std::vector<int>(n + 1);

    for (int i = 0; i < n; ++i)
    {
        if (str[i] == '<')
        {
            arr[i + 1] = arr[i] + 1;
        }
    }

    for (int i = n - 1; i >= 0; --i)
    {
        if (str[i] == '>')
        {
            arr[i] = std::max(arr[i], arr[i + 1] + 1);
        }
    }

    i64 sum = 0;
    for (auto &x: arr)
    {
        sum += x;
    }

    std::cout << sum << "\n";
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
