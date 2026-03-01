#include <iostream>
using namespace std;

int main()
{
    int T = 0;
    cin >> T;

    while (T--)
    {
        long long n = 0, m = 0;
        cin >> n >> m;

        if (n == m)
        {
            cout << 0 << endl;
        }
        else if (((n | m) == m) || ((n | m) == n))
        {
            cout << 1 << endl;
        }
        else
        {
            cout << 2 << endl;
        }
    }
}