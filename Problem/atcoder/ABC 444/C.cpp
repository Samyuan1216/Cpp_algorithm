#include <bits/stdc++.h>
#include <bits/extc++.h>
namespace ranges = std::ranges;
namespace views = std::views;

using i64 = int64_t;
using i128 = __int128;
using u64 = uint64_t;
using u128 = unsigned __int128;
using f64 = double;
using f128 = long double;

template<typename T>
using lim = std::numeric_limits<T>;

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

    ranges::sort(arr);

    auto check = [&](i64 L)
    {
        for (int l = 0, r = n - 1; l <= r; --r)
        {
            if (arr[r] > L)
            {
                return false;
            }

            if (arr[r] != L)
            {
                if (l == r || arr[l] + arr[r] != L)
                {
                    return false;
                }

                l++;
            }
        }

        return true;
    };

    for (auto &L: {arr.back(), arr.front() + arr.back()})
    {
        if (check(L))
        {
            std::cout << L << " ";
        }
    }
    std::cout << "\n";
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
