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
    int n, m;
    std::cin >> n >> m;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    ranges::sort(arr);

    std::vector<int> cnt(m + 1), suf(m + 1);
    for (int i = m, j = n - 1; i >= 0; --i)
    {
        while (j >= 0 && arr[j] == i)
        {
            ++cnt[i];
            --j;
        }

        suf[i] = (i < m? suf[i + 1]: 0) + cnt[i];
    }

    int max = 0;
    for (int i = 0; i <= m; ++i)
    {
        max = std::max(max, suf[i] + (2 * i <= m? cnt[2 * i]: 0));
    }

    std::cout << max << "\n";
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
