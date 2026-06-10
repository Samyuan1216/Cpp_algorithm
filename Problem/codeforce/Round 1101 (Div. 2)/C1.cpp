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
    int n, x, s;
    std::string str;
    std::cin >> n >> x >> s >> str;

    int ans = 0, cnt = ranges::count(str, 'A');
    for (int i = 0; i <= cnt; ++i)
    {
        int res = 0, exist = i;
        std::vector<int> capacity(x);

        for (int j = 0, E = 0, I = 0; j < n; ++j)
        {
            if (E < x && capacity[E] == s)
            {
                ++E;
            }

            if (str[j] == 'E' || (str[j] == 'A' && exist == 0))
            {
                if (E == x || capacity[E] == 0)
                {
                    continue;
                }

                ++capacity[E];
            }
            else
            {
                if (I == x)
                {
                    continue;
                }

                ++capacity[I++];
            }

            ++res;
            if (str[j] == 'A' && exist > 0)
            {
                --exist;
            }
        }

        ans = std::max(ans, res);
    }

    std::cout << ans << "\n";
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
