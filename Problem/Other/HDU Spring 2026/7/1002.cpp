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

    auto a = std::vector(n, std::vector<int>(n));
    for (auto &line: a)
    {
        for (auto &x: line)
        {
            std::cin >> x;
        }
    }

    auto row = ~std::bitset<10010>();
    for (int i = 0; i < n; ++i)
    {
        std::bitset<10010> tmp;
        for (int j = 0; j < n; ++j)
        {
            tmp.set(a[i][j]);
        }

        row &= tmp;
    }

    auto col = ~std::bitset<10010>();
    for (int j = 0; j < n; ++j)
    {
        std::bitset<10010> tmp;
        for (int i = 0; i < n; ++i)
        {
            tmp.set(a[i][j]);
        }

        col &= tmp;
    }

    auto res = row & col;
    std::vector<int> ans;

    for (int i = 1; i <= n * n; ++i)
    {
        if (res[i])
        {
            ans.push_back(i);
        }
    }

    std::cout << std::ssize(ans) << "\n";
    for (int i = 0; i < std::ssize(ans); ++i)
    {
        std::cout << ans[i] << " \n"[i == std::ssize(ans) - 1];
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
