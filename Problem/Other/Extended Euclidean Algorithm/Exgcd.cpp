#include <bits/stdc++.h>

using ll = long long;

ll d, x, y, px, py;

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

ll power(ll num, ll pow, ll mod)
{
    ll ans = 1;
    while (pow > 0)
    {
        if (pow & 1)
        {
            ans = (ans * num) % mod;
        }

        num = (num * num) % mod;
        pow >>= 1;
    }

    return ans;
}

ll fermat(ll num, ll mod)
{
    return power(num, mod - 2, mod);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    ll a = 220, b = 170;
    exgcd(a, b);

    std::cout << "gcd(" << a << ", " << b << ") = " << d << "\n";
    std::cout << "x = " << x << ", " << "y = " << y << "\n";

    ll mod = 1000000007, test = 10000000;
    std::cout << "求逆元测试开始\n";
    for (ll num = 1; num <= test; num++)
    {
        exgcd(num, mod);

        x = (x % mod + mod) % mod;
        if (x != fermat(num, mod))
        {
            std::cout << "出错了\n";
            break;
        }
    }
    std::cout << "求逆元测试结束\n";
}