#include <bits/stdc++.h>
using namespace std;

long double split = (sqrtl(5.0) + 1.0) / 2.0;
int a, b, minn, maxn;

int main()
{
    cin >> a >> b;

    minn = min(a, b);
    maxn = max(a, b);
    if (minn != int((maxn - minn) * split))
    {
        cout << 1 << endl;
    }
    else
    {
        cout << 0 << endl;
    }
}