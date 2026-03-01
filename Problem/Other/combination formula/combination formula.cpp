#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007, LIMIT = 1000;
vector<long long> fac(LIMIT + 1), inv(LIMIT + 1);

long long power(long long x, int p)
{
    long long ans = 1;
    for (; p != 0; p >>= 1)
    {
        if ((p & 1) == 1)
        {
            ans = (ans * p) % MOD;
        }

        p = (p * p) % MOD;
    }

    return ans;
}

int c(int a, int b)
{
    long long ans = fac[a];
    ans = (ans * inv[b]) % MOD;
    ans = (ans * inv[a - b]) % MOD;

    return (int)ans;
}

int main()
{
    fac[1] = 1;
    for (int i = 2; i <= LIMIT; i++)
    {
        fac[i] = ((long long)i * fac[i - 1]) % MOD;
    }

    inv[LIMIT] = power(fac[LIMIT], MOD - 2);
    for (int i = LIMIT - 1; i >= 0; i--)
    {
        inv[i] = ((long long)(i + 1) * inv[i + 1]) % MOD;
    }

    int a = 537, b = 367;
    cout << c(a, b) << endl;
}