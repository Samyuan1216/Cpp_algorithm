#include <iostream>
using namespace std;

int main()
{
    int a[30] = {};
    a[0] = a[1] = 1;

    for (int i = 2; i < 30; i++)
    {
        a[i] = a[i - 1] + a[i - 2];
    }

    int n = 0;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int x = 0;
        cin >> x;
        cout << a[x - 1] << endl;
    }
}