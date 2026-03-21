#include <bits/stdc++.h>
using namespace std;

int s, a, b, x, ans;

int main()
{
    cin >> s >> a >> b >> x;

    ans = x / (a + b) * s * a;
    x %= a + b;

    ans += min(x * s, a * s);

    cout << ans << endl;
}