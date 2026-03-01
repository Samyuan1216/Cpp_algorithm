// https://www.nowcoder.com/share/jump/1961392931766669990423

#include <bits/stdc++.h>

#include <bits/stdc++.h>

using ull = unsigned long long;
using vull = std::vector<ull>;
vull arr{2, 3, 5, 6, 8, 11, 14};
int t;
ull x;
bool status;

void solve()
{
    std::cin >> x;

    status = true;
    for (auto &num: arr)
    {
        if (x == num)
        {
            status = false;
            break;
        }
    }

    if (status)
    {
        std::cout << "Yes\n";
    }
    else
    {
        std::cout << "No\n";
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> t;
    while (t--)
    {
        solve();
    }
}