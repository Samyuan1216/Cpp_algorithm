#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

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

    std::vector<int> arr(n);
    int max = 0;

    for (auto &x: arr)
    {
        std::cin >> x;

        max = std::max(x, max);
    }

    std::vector<std::array<int, 2>> sta;

    for (int i = 0, len = 0; i < n; ++i)
    {
        if (i > 0 && sta.back()[0] != arr[i])
        {
            len = 0;
        }

        sta.push_back({arr[i], ++len});
        if (len == k)
        {
            for (int j = 0; j < k; ++j)
            {
                sta.pop_back();
            }

            len = (!sta.empty()? sta.back()[1]: 0);
        }
    }

    std::cout << std::ssize(sta) << "\n";
    for (int i = 0; i < std::ssize(sta); ++i)
    {
        std::cout << sta[i][0] << " \n"[i == std::ssize(sta) - 1];
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
