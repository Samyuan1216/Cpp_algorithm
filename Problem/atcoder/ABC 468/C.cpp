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

    std::vector<int> p(n);
    for (auto &x: p)
    {
        std::cin >> x;
    }

    std::vector<int> q(n);
    for (auto &x: q)
    {
        std::cin >> x;
    }

    std::vector<int> arr(n);
    ranges::iota(arr, 1);

    int ans = 0;
    do
    {
        if (arr > p && arr < q)
        {
            ++ans;
        }
    } while (ranges::next_permutation(arr).found);

    std::cout << ans << "\n";
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
