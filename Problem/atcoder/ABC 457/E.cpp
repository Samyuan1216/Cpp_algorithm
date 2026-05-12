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

    std::map<std::array<int, 2>, int> mp;
    std::vector<std::vector<int>> lp(n + 1), rp(n + 1);
    std::vector<int> maxl(n + 1, -1e9), minr(n + 2, 1e9);

    for (int i = 0, l, r; i < m; ++i)
    {
        std::cin >> l >> r;

        ++mp[{l, r}];
        lp[l].push_back(r);
        rp[r].push_back(l);
        maxl[r] = std::max(maxl[r], l);
        minr[l] = std::min(minr[l], r);
    }

    for (int i = 1; i <= n; ++i)
    {
        ranges::sort(lp[i]);
        ranges::sort(rp[i]);
    }

    for (int i = 1; i <= n; ++i)
    {
        maxl[i] = std::max(maxl[i], maxl[i - 1]);
    }

    for (int i = n; i >= 1; --i)
    {
        minr[i] = std::min(minr[i], minr[i + 1]);
    }

    int q;
    std::cin >> q;

    while (q--)
    {
        int s, t;
        std::cin >> s >> t;

        if (mp.contains({s, t}))
        {
            if (mp[{s, t}] >= 2)
            {
                std::cout << "Yes\n";
                continue;
            }

            bool status = false;
            if (s + 1 <= n)
            {
                status = (minr[s + 1] <= t);
            }

            if (!status && t - 1 >= 1)
            {
                status = (maxl[t - 1] >= s);
            }

            std::cout << (status? "Yes\n": "No\n");
            continue;
        }

        auto lit = ranges::lower_bound(rp[t], s);
        auto rit = ranges::upper_bound(lp[s], t);

        if (lit == rp[t].end() || rit == lp[s].begin())
        {
            std::cout << "No\n";
            continue;
        }

        int l = *lit, r = *std::prev(rit);
        std::cout << (r + 1 >= l? "Yes\n": "No\n");
    }
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
