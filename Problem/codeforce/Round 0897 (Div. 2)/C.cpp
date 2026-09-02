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
    std::cin >> n;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    ranges::sort(arr);

    int mex = 0;
    for (int i = 0; i < n; ++i)
    {
        if (arr[i] != mex)
        {
            break;
        }

        ++mex;
    }

    while (true)
    {
        std::cout << mex << std::endl;

        int y;
        std::cin >> y;

        if (y == -1)
        {
            break;
        }

        mex = y;
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
