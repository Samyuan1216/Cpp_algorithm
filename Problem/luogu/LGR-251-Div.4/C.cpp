#include <bits/stdc++.h>
using namespace std;

int n;

int main()
{
    cin >> n;

    while (n >= 10)
    {
        if (n >= 10 && n % 10 != 0)
        {
            cout << "No" << endl;
            return 0;
        }

        n /= 10;
    }

    cout << "Yes" << endl;
}