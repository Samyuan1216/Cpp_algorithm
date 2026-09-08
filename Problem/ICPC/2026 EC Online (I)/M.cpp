#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

void solve()
{
    int n, m;
    std::cin >> n >> m;

    std::map<std::string, bool> should;
    for (int i = 0; i < n; ++i)
    {
        std::string str;
        std::cin >> str;

        should.insert({str, false});
    }

    for (int i = 0; i < m; ++i)
    {
        std::string str;
        std::cin >> str;

        if (!should.contains(str))
        {
            std::cout << "WRONG\n";
        }
        else if (should[str])
        {
            std::cout << "REPEAT\n";
        }
        else
        {
            should[str] = true;
            std::cout << "OK\n";
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    // std::cin >> t;
    while (t--)
    {
        solve();
    }
}
