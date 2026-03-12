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
    int n;
    std::cin >> n;

    auto a = std::vector<int>(n);
    for (auto &x: a)
    {
        std::cin >> x;
    }

    auto b = std::vector<int>(n);
    for (auto &x: b)
    {
        std::cin >> x;
    }

    ranges::sort(a);
    ranges::sort(b);

    if (a == b)
    {
        std::cout << "Yes\n";
        return;
    }

    int acnt = 0, bcnt = 0;
    for (int i = 0; i < n; ++i)
    {
        if (a[i] & 1)
        {
            ++acnt;
        }
        
        if (b[i] & 1)
        {
            ++bcnt;
        }
    }

    if (acnt != bcnt)
    {
        std::cout << "No\n";
        return;
    }

    auto check = [&](auto &&arr)
    {
        for (int i = 0; i < n; ++i)
        {
            if (arr[i] == arr[i + 1] - 1)
            {
                return true;
            }
        }

        return false;
    };

    std::cout << (check(a) && check(b)? "Yes\n": "No\n");
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
