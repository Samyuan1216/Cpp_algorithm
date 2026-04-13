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
    int n;
    std::cin >> n;

    int mina = lim<int>::max();
    auto arr = std::vector<int>(n);
    for (auto &x: arr)
    {
        std::cin >> x;

        mina = std::min(mina, x);
    }

    int ans = 0;
    while (true)
    {
        bool status = true;
        for (int i = 1; i < n; ++i)
        {
            if (arr[i] != arr[i - 1])
            {
                status = false;
                break;
            }
        }

        if (status)
        {
            break;
        }

        ++ans;
        for (auto &x: arr)
        {
            x = (x + mina) / 2;
        }
    }

    std::cout << ans << "\n";

    if (ans <= n)
    {
        for (int i = 1; i <= ans; ++i)
        {
            std::cout << mina << " \n"[i == ans];
        }
    }
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
