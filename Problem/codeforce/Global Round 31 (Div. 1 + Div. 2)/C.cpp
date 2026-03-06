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
    int n, k;
    std::cin >> n >> k;

    std::vector<int> ans(k);
    std::vector<bool> unfree(k, true);
    for (int i = std::bit_width(unsigned(n)) - 1, cnt = k; i >= 0; --i)
    {
        int num;
        if (n & (1 << i))
        {
            num = (k - 1) % 2;
        }
        else
        {
            num = k - (k - cnt) / 2 * 2;
        }

        for (int j = 0; j < k; ++j)
        {
            if (num > 0 && unfree[j])
            {
                --num;
            }
            else
            {
                ans[j] |= (1 << i);
            }
        }

        for (int j = 0; j < k; ++j)
        {
            if (num > 0 && (ans[j] & (1 << i)))
            {
                ans[j] ^= (1 << i);
                --num;
            }

            if ((n & (1 << i)) && (ans[j] & (1 << i)) == 0)
            {
                unfree[j] = false;
                --cnt;
            }
        }
    }

    for (int i = 0; i < k; ++i)
    {
        std::cout << ans[i] << " \n"[i == k - 1];
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
