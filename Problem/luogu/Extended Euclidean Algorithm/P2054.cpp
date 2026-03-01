#include <bits/stdc++.h>

using ll = long long;

ll n, m, l, mod, d, x, y, px, py;

ll multiply(ll a, ll b)
{
    a = (a % mod + mod) % mod;
    b = (b % mod + mod) % mod;

    ll ans = 0;
    while (b > 0)
    {
        if (b & 1)
        {
            ans = (ans + a) % mod;
        }

        a = (a + a) % mod;
        b >>= 1;
    }

    return ans;
}

ll power(ll a, ll b)
{
    ll ans = 1;
    while (b > 0)
    {
        if (b & 1)
        {
            ans = multiply(ans, a);
        }

        a = multiply(a, a);
        b >>= 1;
    }

    return ans;
}

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

    std::cin >> n >> m >> l;
    mod = n + 1;

    exgcd(power(2, m), mod);
    std::cout << multiply((x % mod + mod) % mod, l);
}