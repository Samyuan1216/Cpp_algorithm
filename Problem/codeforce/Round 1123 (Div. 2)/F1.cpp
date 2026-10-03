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

    ranges::sort(arr);

    int m = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            ++m;
        }
    }

    std::vector<int> ans{arr[n - 1] - arr[0]}, b(m);
    while (true)
    {
        int idx = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                b[idx++] = arr[i] ^ arr[j];
            }
        }

        ranges::sort(b);

        for (int i = 0; i < n; ++i)
        {
            arr[i] = b[i];
        }

        ans.push_back(arr[n - 1] - arr[0]);
        if (ans.back() == 0)
        {
            break;
        }
    }

    while (q--)
    {
        int x;
        std::cin >> x;
        std::cout << ans[std::min(x, int(std::ssize(ans) - 1))] << "\n";
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
