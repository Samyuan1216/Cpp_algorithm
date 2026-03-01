#include <iostream>
using namespace std;

int main()
{
    int T = 0;
    cin >> T;

    while (T--)
    {
        int a = 0, b = 0;
        cin >> a >> b;

        if ((a == 0 && ((b & 1) == 0)) || (a > 0 && ((b & 1) == 1)))
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
}