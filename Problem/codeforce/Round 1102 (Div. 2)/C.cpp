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

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    {
        auto tmp = arr;
        arr.insert(arr.end(), tmp.begin(), tmp.end());
    }

    auto compute = [&](int idx) -> i64
    {
        i64 res = 0;
        for (i64 l = idx, r = idx + n - 1, bottom = 0; l < r;)
        {
            res += std::max(0ll, std::min(arr[l], arr[r]) - bottom) * (r - l);
            bottom = std::max(std::min(arr[l], arr[r]), bottom);

            if (arr[l] < arr[r])
            {
                ++l;
            }
            else
            {
                --r;
            }
        }

        return res;
    };

    for (int i = 0; i < n; ++i)
    {
        std::cout << compute(i) << " \n"[i == n - 1];
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
