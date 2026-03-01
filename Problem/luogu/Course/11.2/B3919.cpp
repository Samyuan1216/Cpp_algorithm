#include <iostream>
using namespace std;

int main()
{
    unsigned int n = 0, ans = 0;
    int q = 0;
    cin >> n >> q;

    while (q--)
    {
        int k = 0;
        cin >> k;

        k--;
        unsigned int next_n = n | (1 << k);
        if (next_n != n)
        {
            next_n &= ~((1 << k) - 1);
        }

        ans += next_n - n;
        n = next_n;
    }

    cout << ans << endl;
}