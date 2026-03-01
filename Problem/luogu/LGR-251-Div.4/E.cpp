#include <bits/stdc++.h>
using namespace std;

bool status = true;
int t, n, pre, cur;

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;
        status = true;

        cin >> pre;
        for (int i = 2; i <= n; i++)
        {
            cin >> cur;
            if ((((i - 1) & 1) == 0 && pre == cur) || (((i - 1) & 1) == 1 && pre != cur))
            {
                status = false;
                i++;
                for (i; i <= n; i++)
                {
                    cin >> cur;
                }
            }
            pre = cur;
        }

        if (status)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
}