#include <bits/stdc++.h>

using ll = long long;

ll a, b, d, x, y, px, py;

void exgcd(ll a, ll b)
{
    if (b == 0)
    {
        d = a, x = 1, y = 0;
    }
    else
    {
        exgcd(b, a % b);

        px = x, py = y;
        x = py, y = px - py * (a / b);
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> a >> b;
    exgcd(a, b);

    std::cout << (x % b + b) % b << "\n";
}