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
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    std::vector<int> idx(k);
    for (auto &x: idx)
    {
        std::cin >> x;

        --x;
    }

    int max = 0, sum = 0, cnt = 0;
    for (int i = 0, j = 0, num = arr[idx[0]]; i < n; ++i)
    {
        if (j < k && i == idx[j])
        {
            max = std::max(max, cnt);
            cnt = 0;

            ++j;
        }
        else if ((i == 0 || arr[i] != arr[i - 1]) && arr[i] != num)
        {
            ++cnt;
            ++sum;
        }
    }

    max = 2 * std::max(max, cnt);

    std::cout << std::max(max, sum) << "\n";
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
