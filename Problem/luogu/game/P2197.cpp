#include <bits/stdc++.h>
using namespace std;

int t, n, a, ans;

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;

        ans = 0;
        while (n--)
        {
            cin >> a;
            ans ^= a;
        }

        if (ans)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
}