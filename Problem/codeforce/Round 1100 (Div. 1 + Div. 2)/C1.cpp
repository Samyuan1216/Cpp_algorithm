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
    }

    std::vector<int> ans;
    for (int i = 0, j = -1; i < n; ++i)
    {
        if (i > 0 && arr[i - 1] < 0 && arr[i] > 0)
        {
            j = i - 1;
        }

        if (arr[i] > 0 && (i + 1 == n || arr[i + 1] < 0))
        {
            ans.push_back(i);
            if (j != -1)
            {
                ans.push_back(j);
            }
        }
    }

    std::cout << ans.size() << "\n";
    for (auto &x: ans)
    {
        std::cout << x + 1 << " ";
    }
    std::cout << "\n";
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
