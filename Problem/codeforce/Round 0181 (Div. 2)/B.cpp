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

    std::vector<int> ord(n, -1);
    std::vector<std::vector<int>> team(n);
    int cnt = 0;

    while (m--)
    {
        int x, y;
        std::cin >> x >> y;
        --x, --y;

        if (ord[x] >= 0 && ord[y] >= 0)
        {
            if (ord[x] == ord[y])
            {
                continue;
            }
            else
            {
                std::cout << -1 << "\n";
                return;
            }
        }

        int idx = std::max(ord[x], ord[y]);
        if (idx == -1)
        {
            team[cnt].push_back(x);
            team[cnt].push_back(y);

            idx = cnt++;
        }
        else
        {
            if (ord[x] == -1)
            {
                team[idx].push_back(x);
            }
            else
            {
                team[idx].push_back(y);
            }
        }

        ord[x] = ord[y] = idx;
    }

    for (int i = 0, j = 0; i < n; ++i)
    {
        while (j < n / 3 && std::ssize(team[j]) >= 3)
        {
            ++j;
        }

        if (ord[i] == -1)
        {
            team[j].push_back(i);
        }
    }

    for (int i = 0; i < n / 3; ++i)
    {
        auto &t = team[i];
        if (std::ssize(t) != 3)
        {
            std::cout << -1 << "\n";
            return;
        }
    }

    for (int i = 0; i < n / 3; ++i)
    {
        auto &t = team[i];
        std::cout << t[0] + 1 << " " << t[1] + 1 << " " << t[2] + 1 << "\n";
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
