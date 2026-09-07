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

    std::vector<std::array<int, 2>> arr(n);
    int mina = 2e9;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> arr[i][0] >> arr[i][1];

        if (arr[i][0] < mina)
        {
            mina = arr[i][0];
        }
    }

    i64 ans = 0;
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
