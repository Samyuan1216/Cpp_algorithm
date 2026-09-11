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

    std::vector<int> in(n);
    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        ++in[u], ++in[v];
    }

    std::string str;
    std::cin >> str;

    int c0 = 0, c1 = 0, m = 0, q = 0;
    for (int i = 1; i < n; ++i)
    {
        if (in[i] == 1)
        {
            if (str[i] == '0')
            {
                ++c0;
            }
            else if (str[i] == '1')
            {
                ++c1;
            }
            else
            {
                ++m;
            }
        }
        else if (str[i] == '?')
        {
            ++q;
        }
    }

    if (str[0] != '?')
    {
        std::cout << (str[0] == '1'? c0: c1) + (m + 1) / 2 << "\n";
    }
    else if (c0 != c1)
    {
        std::cout << std::max(c0, c1) + m / 2 << "\n";
    }
    else
    {
        std::cout << c0 + (q & 1? m + 1: m) / 2 << "\n";
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
