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
    int n;
    std::cin >> n;

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    ranges::sort(arr, std::greater());

    std::vector<i64> odd, even;
    for (int i = 2; i < n; ++i)
    {
        if (arr[i] & 1)
        {
            odd.push_back(arr[i]);
        }
        else
        {
            even.push_back(arr[i]);
        }
    }

    std::vector<i64> res(n);
    res[0] = arr[0], res[n - 1] = arr[1];

    bool status = (arr[0] & 1? true: false);
    for (int i = 1; i < n - 1; ++i)
    {
        if (odd.empty())
        {
            res[i] = even.back();
            even.pop_back();
        }
        else if (even.empty())
        {
            res[i] = odd.back();
            odd.pop_back();
        }
        else
        {
            if (status)
            {
                res[i] = even.back();
                even.pop_back();
            }
            else
            {
                res[i] = odd.back();
                odd.pop_back();
            }

            status = !status;
        }
    }

    i64 ans = 0;
    for (int i = 1; i < n; ++i)
    {
        ans += (res[i - 1] + res[i]) / 2;
    }

    std::cout << ans << "\n";
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