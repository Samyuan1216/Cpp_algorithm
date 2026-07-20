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

    if (ranges::is_sorted(arr))
    {
        std::cout << 0 << "\n";
        return;
    }

    for (int p = 0;; ++p)
    {
        bool status = true;
        for (int i = 0, pre = -1; i < n; i += 1 << (p + 1))
        {
            int min = *ranges::min_element(arr.begin() + i, arr.begin() + std::min(n, i + (1 << (p + 1))));
            if (i > 0 && pre > min)
            {
                status = false;
                break;
            }

            pre = *ranges::max_element(arr.begin() + i, arr.begin() + std::min(n, i + (1 << (p + 1))));
        }

        if (status)
        {
            std::cout << (1 << p) << "\n";
            return;
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
