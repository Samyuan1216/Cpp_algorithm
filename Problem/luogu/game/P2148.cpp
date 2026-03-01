#include <bits/stdc++.h>
using namespace std;

int t, n, a, b;

int low_zero(int status)
{
    int cnt = 0;
    while (status > 0)
    {
        if ((status & 1) == 0)
        {
            break;
        }

        cnt++;
        status >>= 1;
    }

    return cnt;
}

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;

        int sg = 0;
        while (n)
        {
            cin >> a >> b;

            sg ^= low_zero((a - 1) | (b - 1));
            n -= 2;
        }

        if (sg)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
}