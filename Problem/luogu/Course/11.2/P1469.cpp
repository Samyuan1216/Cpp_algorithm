#include <iostream>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);

    int n = 0;
    cin >> n;

    int res = 0;
    for (int i = 0; i < n; i++)
    {
        int x = 0;
        cin >> x;

        res ^= x;
    }

    cout << res;
}