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

    std::vector<bool> is(n);
    int cnt = 0;

    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;

        is[i] = (std::popcount(unsigned(x)) % 2 == 0);
        if (is[i])
        {
            ++cnt;
        }
    }

    std::cout << cnt << " \n"[q == 0];
    while (q--)
    {
        int p, x;
        std::cin >> p >> x;
        --p;

        bool status = (std::popcount(unsigned(x)) % 2 == 0);
        if (is[p] && !status)
        {
            --cnt;
        }
        else if (!is[p] && status)
        {
            ++cnt;
        }

        is[p] = status;
        std::cout << cnt << " \n"[q == 0];
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
