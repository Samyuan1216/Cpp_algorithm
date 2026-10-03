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

    std::vector<int> odd, even;
    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;

        if (i & 1)
        {
            odd.push_back(x);
        }
        else
        {
            even.push_back(x);
        }
    }

    ranges::sort(odd), ranges::sort(even);

    int l = 0, r = n - 1;
    int oidx = 0, eidx = 0;

    std::vector<int> res(n);
    bool is_odd = false;

    if (n % 2 == 0)
    {
        res[0] = even[eidx++];
        l = 1;
        is_odd = true;
    }

    for (; l <= r; ++l, --r)
    {
        auto &a = (is_odd? odd: even);
        int &idx = (is_odd? oidx: eidx);

        if (l == r)
        {
            res[l] = a[idx];
            break;
        }

        int small = a[idx++], big = a[idx++];
        if (small > big)
        {
            std::swap(small, big);
        }

        if (l == 0 || small > res[l - 1])
        {
            res[l] = small, res[r] = big;
        }
        else
        {
            res[l] = big, res[r] = small;
        }

        is_odd = !is_odd;
    }

    bool status = false;
    for (int i = 0; i < n - 1; ++i)
    {
        if (!status && res[i] > res[i + 1])
        {
            status = true;
        }
        else if (status && res[i] < res[i + 1])
        {
            std::cout << "NO\n";
            return;
        }
    }

    std::cout << "YES\n";
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
