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
    std::string str;
    std::cin >> n >> q >> str;

    i64 w = 0;
    for (int i = 1; i < n; ++i)
    {
        if (str[i] == str[i - 1])
        {
            continue;
        }

        w += 1ll * i * (n - i);
    }

    i64 cnt0 = ranges::count(str, '0'), cnt1 = ranges::count(str, '1');
    std::cout << (w + cnt0 * cnt1) / 2;

    while (q--)
    {
        int p;
        std::cin >> p;
        --p;

        for (auto i: {p, p + 1})
        {
            if (i < 1 || i >= n)
            {
                continue;
            }

            i64 tmp = 1ll * i * (n - i);
            w += (str[i - 1] == str[i]? tmp: -tmp);
        }

        cnt0 += (str[p] == '0'? -1: 1);
        cnt1 += (str[p] == '1'? -1: 1);
        str[p] = (str[p] == '0'? '1': '0');

        std::cout << " " << (w + cnt0 * cnt1) / 2;
    }
    std::cout << "\n";
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
