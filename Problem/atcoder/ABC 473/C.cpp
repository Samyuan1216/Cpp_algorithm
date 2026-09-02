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
    int n, k;
    std::cin >> n >> k;

    std::vector<int> c(k);
    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;
        --x;

        ++c[x];
    }

    int max = -1, cnt = 0, submax = -1, subcnt = 0;
    for (int i = 0; i < k; ++i)
    {
        if (c[i] > max)
        {
            submax = max;
            subcnt = cnt;
            max = c[i];
            cnt = 1;
        }
        else if (c[i] == max)
        {
            ++cnt;
        }
        else if (c[i] > submax)
        {
            submax = c[i];
            subcnt = 1;
        }
        else if (c[i] == submax)
        {
            ++subcnt;
        }
    }

    int ans = cnt;
    if (submax + 1 == max)
    {
        ans += subcnt;
    }

    std::cout << ans << "\n";
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
