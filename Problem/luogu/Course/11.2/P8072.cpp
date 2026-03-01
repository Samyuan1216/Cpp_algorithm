#include <iostream>
using namespace std;

int main()
{
    int k = 0;
    cin >> k;

    if ((k & (k - 1)) == 0)
    {
        cout << k << " " << 0 << endl;
    }
    else
    {
        int n = 1 << (32 - __builtin_clz(k));
        int bit_width = 32 - __builtin_clz(k) - __builtin_ctz(k);
        cout << n << " " << bit_width << endl;
    }
}