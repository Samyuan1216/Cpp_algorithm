#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

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
    std::vector<int> sg(101);
    for (int i = 1; i <= 100; ++i)
    {
        std::vector<int> tmp;
        for (int j = i - 1; j >= 1; --j)
        {
            if (std::gcd(i, j) > 1)
            {
                tmp.push_back(sg[j]);
            }
        }

        ranges::sort(tmp);

        int mex = 0;
        for (auto &x: tmp)
        {
            if (x == mex)
            {
                ++mex;
            }
        }

        sg[i] = mex;
    }

    for (int i = 1; i <= 100; ++i)
    {
        std::cout << i << ": " << sg[i] << "\n";
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    // std::cin >> t;
    while (t--)
    {
        solve();
    }
}
