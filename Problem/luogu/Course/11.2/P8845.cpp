#include <iostream>
using namespace std;

int main()
{
    int T = 0;
    cin >> T;

    while (T--)
    {
        int x = 0, y = 0;
        cin >> x >> y;

        if ((x == 1 && y == 2) || (x == 2 && y == 1))
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
}