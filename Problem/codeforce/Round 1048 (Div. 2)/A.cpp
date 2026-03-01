#include <iostream>
using namespace std;

int t, x, y;

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> x >> y;

        if (x == y)
        {
            cout << 0 << endl;
        }
        else if (x % y == 0 || y % x == 0)
        {
            cout << 1 << endl;
        }
        else
        {
            cout << 2 << endl;
        }
    }

    return 0;
}