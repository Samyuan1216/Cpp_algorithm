#include <bits/stdc++.h>
using namespace std;

int n, m;

int main()
{
    cin >> n;
    while (n--)
    {
        cin >> m;

        if (m & 1)
        {
            cout << "zs wins" << endl;
        }
        else
        {
            cout << "pb wins" << endl;
        }
    }
}