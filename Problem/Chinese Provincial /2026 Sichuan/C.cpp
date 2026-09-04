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
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<std::set<int>> beat(n);
    for (int i = 0, s, x; i < n; ++i)
    {
        std::cin >> s;
        while (s--)
        {
            std::cin >> x;
            --x;

            beat[i].insert(x);
        }
    }

    std::set<int> cur;
    std::vector<int> rubbish;

    int ans = 0;
    for (int i = 0, x; i < m; ++i)
    {
        std::cin >> x;
        --x;

        if (cur.empty())
        {
            cur = beat[x];
            ++ans;

            continue;
        }

        for (auto &t: cur)
        {
            if (!beat[x].contains(t))
            {
                rubbish.push_back(t);
            }
        }

        bool status = false;
        if (std::ssize(rubbish) == std::ssize(cur))
        {
            for (auto &t: rubbish)
            {
                if (!beat[t].contains(x))
                {
                    status = true;
                    break;
                }
            }
        }

        for (auto &t: rubbish)
        {
            cur.erase(t);
        }

        rubbish.clear();

        if (cur.empty() && !status)
        {
            ++ans;
            cur = beat[x];
        }
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
