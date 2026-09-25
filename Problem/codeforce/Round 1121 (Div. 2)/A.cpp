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
        --x;
    }

    for (int l = 0, r = n - 1; l < r;)
    {
        while (l < n && arr[l] == l)
        {
            ++l;
        }

        while (r >= 0 && arr[r] == r)
        {
            --r;
        }

        if (l < r)
        {
            std::swap(arr[l], arr[r]);
            ++l, --r;
        }
    }

    std::cout << (ranges::is_sorted(arr)? "YES\n": "NO\n");
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
