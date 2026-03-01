#include <bits/stdc++.h>
using namespace std;

int a, b, c, d;

int main()
{
    cin >> a >> b >> c >> d;
    if ((a == b) || (a == c) || (b == c))
    {
        cout << "Report" << endl;
        return 0;
    }

    if (d == a)
    {
        cout << "A" << endl;
    }
    else if (d == b)
    {
        cout << "B" << endl;
    }
    else if (d == c)
    {
        cout << "C" << endl;
    }
    else
    {
        if ((a < b && a > c) || (a < c && a > b))
        {
            cout << "A" << endl;
        }
        else if ((b < a && b > c) || (b < c && b > a))
        {
            cout << "B" << endl;
        }
        else
        {
            cout << "C" << endl;
        }
    }
}