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

    std::vector<int> color(n);
    std::vector<std::array<int, 3>> query(n);
    int sum = 0;

    for (auto &[d, a, b]: query)
    {
        std::cin >> a >> d >> b;
        --a, --b;

        if (++color[a] == 1)
        {
            ++sum;
        }
    }

    ranges::sort(query);

    for (int i = 1, j = 0; i <= m; ++i)
    {
        while (j < n && query[j][0] <= i)
        {
            if (--color[query[j][1]] == 0)
            {
                --sum;
            }

            if (++color[query[j][2]] == 1)
            {
                ++sum;
            }

            ++j;
        }

        std::cout << sum << "\n";
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
