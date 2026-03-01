#include <iostream>
using namespace std;

int main()
{
    int a[5] = {};
    for (auto &x: a)
    {
        cin >> x;
    }

    int sum = 0;
    for (int i = 0; i < 5; i++)
    {
        sum += a[i] % 3;
        a[i] -= a[i] % 3;

        a[(i + 1) % 5] += a[i] / 3;
        a[(i - 1 + 5) % 5] += a[i] / 3;

        a[i] /= 3;
    }

    for (auto &x: a)
    {
        cout << x << " ";
    }

    cout << endl;
    cout << sum << endl;
}