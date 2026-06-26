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
    for (int i = 1; auto &[x, id]: arr)
    {
        std::cin >> x;

        id = i++;
    }

    ranges::sort(arr);
    for (int i = 0; i < 3; ++i)
    {
        std::cout << arr[i][1] << " \n"[i == 2];
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
