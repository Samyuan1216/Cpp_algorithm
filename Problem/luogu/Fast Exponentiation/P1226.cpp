#include <bits/stdc++.h>
using namespace std;

long long a = 0, b = 0, p = 0;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b >> p;
    cout << a << "^" << b << " mod " << p << "=";

    long long ans = 1;
    while (b > 0)
    {
        if ((b & 1) == 1)
        {
            ans = (ans * a) % p;
        }

        a = (a * a) % p;
        b >>= 1;
    }

    cout << ans << endl;
}