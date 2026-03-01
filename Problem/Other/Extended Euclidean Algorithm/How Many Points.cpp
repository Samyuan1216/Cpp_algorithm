// https://lightoj.com/problem/how-many-points

#include <bits/stdc++.h>

using ll = long long;

ll t, xa, ya, xb, yb;

ll gcd(ll a, ll b)
{
    return (b == 0? a: gcd(b, a % b));
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> t;
    for (ll i = 1; i <= t; i++)
    {
        std::cin >> xa >> ya >> xb >> yb;
        std::cout << "Case " << i << ": " << gcd(std::abs(xa - xb), std::abs(ya - yb)) + 1 << "\n";
    }
}