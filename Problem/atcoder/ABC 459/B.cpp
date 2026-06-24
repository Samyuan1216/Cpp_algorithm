#include <bits/extc++.h>

using i64 = long long;

void solve()
{
    int n;
    std::cin >> n;

    std::vector<std::string> strs(n);
    for (auto &str: strs)
    {
        std::cin >> str;
    }

    auto compute = [&](int c) -> int
    {
        if (c >= 0 && c <= 2)
        {
            return 2;
        }
        else if (c >= 3 && c <= 5)
        {
            return 3;
        }
        else if (c >= 6 && c <= 8)
        {
            return 4;
        }
        else if (c >= 9 && c <= 11)
        {
            return 5;
        }
        else if (c >= 12 && c <= 14)
        {
            return 6;
        }
        else if (c >= 15 && c <= 18)
        {
            return 7;
        }
        else if (c >= 19 && c <= 21)
        {
            return 8;
        }
        else
        {
            return 9;
        }

        return -1;
    };

    for (auto &str: strs)
    {
        std::cout << compute(str[0] - 'a');
    }
    std::cout << "\n";
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
