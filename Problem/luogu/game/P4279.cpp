#include <bits/stdc++.h>
using namespace std;

bool status;
int t, n, a, ans;

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;

        ans = 0;
        status = true;
        while (n--)
        {
            cin >> a;
            
            ans ^= a;
            if (a > 1)
            {
                status = false;
            }
        }

        if (status)
        {
            if (!ans)
            {
                cout << "John" << endl;
            }
            else
            {
                cout << "Brother" << endl;
            }
        }
        else
        {
            if (ans)
            {
                cout << "John" << endl;
            }
            else
            {
                cout << "Brother" << endl;
            }
        }
    }
}