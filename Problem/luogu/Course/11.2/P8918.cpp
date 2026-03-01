#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int T = 0;
    cin >> T;

    while (T--)
    {
        int x = 0;
        cin >> x;

        if ((x & 1) == 1)
        {
            int i = 0;
            while (x >= (int)pow(2, i))
            {
                i++;
            }

            cout << i << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }
}