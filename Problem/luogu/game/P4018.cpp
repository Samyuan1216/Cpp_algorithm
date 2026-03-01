#include <bits/stdc++.h>
using namespace std;

int t, n;

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;
        if (n % 6 != 0)
        {
            cout << "October wins!" << endl;
        }
        else
        {
            cout << "Roy wins!" << endl;
        }
    }
}