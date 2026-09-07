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
    int n, q;
    std::cin >> n >> q;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    std::vector<std::array<int, 2>> time(n);
    for (int i = 0; i < n; ++i)
    {
        time[arr[i] - 1][0] = i;
        time[i][1] = i + 1;
    }

    int t = n;
    while (q--)
    {
        int x;
        std::cin >> x;
        --x;

        time[x][0] = t++;
    }

    ranges::sort(time);

    for (int i = 0; i < n; ++i)
    {
        std::cout << time[i][1] << " \n"[i == n - 1];
    }
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
