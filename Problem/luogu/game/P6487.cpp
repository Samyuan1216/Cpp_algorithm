#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;

const ll MAXN = 1000000000000010, MAXM = 110;
vll fib(MAXM);
int siz = 1, m, idx;
ll n, ans;

void build()
{
    fib[0] = 1;
    fib[1] = 2;
    while (fib[siz] <= MAXN)
    {
        siz++;
        fib[siz] = fib[siz - 1] + fib[siz - 2];
    }
}

int main()
{
    build();

    cin >> n;

    while (1)
    {
        for (int l = 0, r = siz, m; l <= r;)
        {
            m = l + ((r - l) >> 1);
            if (n >= fib[m])
            {
                idx = m;
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }

        if (n == fib[idx])
        {
            ans = fib[idx];
            break;
        }
        else
        {
            n -= fib[idx];
        }
    }

    cout << ans << endl;
}