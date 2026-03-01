// https://www.nowcoder.com/share/jump/1961392931766318984042

#include <bits/stdc++.h>

int a, b, x;

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> a >> b >> x;
    a -= x / 2, b -= x / 2;

    if (a < 0 || b < 0 || (a & 1) == 1 || (b & 1) == 1)
    {
        std::cout << -1 << "\n";
        return 0;
    }

    while (a--)
    {
        std::cout << 0;
    }

    while (x--)
    {
        std::cout << ((x & 1) == 0? 0: 1);
    }

    while (b--)
    {
        std::cout << 1;
    }

    std::cout << "\n";
}