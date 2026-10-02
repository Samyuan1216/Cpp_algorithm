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

    std::array<int, 101> cnt{};
    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;

        ++cnt[x];
    }

    std::vector<int> ans;
    while (true)
    {
        bool add = false;

        for (int i = 100; i >= 1; --i)
        {
            if (cnt[i] > 0)
            {
                ans.push_back(i);
                add = true;
                --cnt[i];
            }
        }

        if (!add)
        {
            break;
        }
    }

    for (int i = 0; i < n; ++i)
    {
        std::cout << ans[i] << " \n"[i == n - 1];
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
