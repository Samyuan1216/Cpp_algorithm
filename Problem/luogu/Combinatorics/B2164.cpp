#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const int MAXN = 5000, MOD = 1000000007;
vll fac(MAXN + 1), inv(MAXN + 1);
ll n, m;

ll power(ll x, ll p)
{
    ll ans = 1;
    while (p > 0)
    {
        if (p & 1)
        {
            ans = (ans * x) % MOD;
        }

        x = (x * x) % MOD;
        p >>= 1;
    }

    return ans;
}

void build(ll n)
{
    fac[1] = 1;
    for (ll i = 2; i <= n; i++)
    {
        fac[i] = (ll(i) * fac[i - 1]) % MOD;
    }

    inv[n] = power(fac[n], MOD - 2);
    for (int i = n - 1; i >= 0; i--)
    {
        inv[i] = (ll(i + 1) * inv[i + 1]) % MOD;
    }
}

ll c()
{
    ll ans = fac[n];
    ans = (ans * inv[m]) % MOD;
    ans = (ans * inv[n - m]) % MOD;

    return ans;
}

int main()
{
    cin >> n >> m;
    build(n);

    cout << c() << endl;
}