#include <iostream>
#include <bitset>
using namespace std;

int main()
{
    long long x = 0;
    cin >> x;

    bitset<32> bx(x), bres;
    for (int i = 16; i < 32 + 16; i++)
    {
        bres[i - 16] = bx[i % 32];
    }

    cout << bres.to_ullong() << endl;
}