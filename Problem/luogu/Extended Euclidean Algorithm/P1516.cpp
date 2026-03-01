#include <bits/stdc++.h>

using ll = long long;

ll x1, x2, m, n, l, a, c, x0, xd, d, x, y, px, py;

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

    std::cin >> x1 >> x2 >> m >> n >> l;
    if (x1 < x2)
    {
        a = m - n, c = x2 - x1;
    }
    else
    {
        a = n - m, c = x1 - x2;
    }

    if (a < 0)
    {
        a = -a, c = l - c;
    }

    exgcd(a, l);

    if (c % d != 0)
    {
        std::cout << "Impossible\n";
    }
    else
    {
        x0 = x * c / d, xd = l / d;
        if (x0 < 0)
        {
            x0 += (1 - x0 + xd - 1) / xd * xd;
        }
        else
        {
            x0 -= (x0 - 1) / xd * xd;
        }

        std::cout << x0 << "\n";
    }
}