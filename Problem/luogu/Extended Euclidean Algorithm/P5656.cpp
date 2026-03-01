#include <bits/stdc++.h>

using ll = long long;

ll t, a, b, c, xd, yd, times, d, x, y, px, py;

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

    std::cin >> t;
    while (t--)
    {
        std::cin >> a >> b >> c;
        exgcd(a, b);

        if (c % d != 0)
        {
            std::cout << -1 << "\n";
        }
        else
        {
            x *= c / d, y *= c / d;
            xd = b / d, yd = a / d;

            if (x < 0)
            {
                times = (1 - x + xd - 1) / xd;
                x += xd * times;
                y -= yd * times;
            }
            else
            {
                times = (x - 1) / xd;
                x -= xd * times;
                y += yd * times;
            }

            if (y <= 0)
            {
                std::cout << x << " " << y + yd * ((1 - y + yd - 1) / yd) << "\n";
            }
            else
            {
                std::cout << (y - 1) / yd + 1 << " " << x << " " << y - (y - 1) / yd * yd << " " << x + (y - 1) / yd * xd << " " << y << "\n";
            }
        }
    }
}