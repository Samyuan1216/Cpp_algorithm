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
    int n, x;
    std::cin >> n >> x;

    auto arr = std::vector<int>(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    bool status = true;
    for (int i = 0; i < n - 1; ++i)
    {
        if (arr[i] <= arr[i + 1])
        {
            if (arr[i + 1] - arr[i] > 1)
            {
                status = false;
                break;
            }
        }
        else
        {
            if (arr[i] - arr[i + 1] > x)
            {
                status = false;
                break;
            }
        }
    }

    std::cout << (status? "Win\n": "Lose\n");
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
