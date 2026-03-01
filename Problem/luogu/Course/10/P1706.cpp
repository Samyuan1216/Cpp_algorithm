#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;

    vector<int> a(n);
    for (int i = 1; i <= n; i++)
    {
        a[i - 1] = i;
    }

    do
    {
        for (auto &x: a)
        {
            printf("%5d", x);
        }

        cout << endl;
    } while (next_permutation(a.begin(), a.end()));
    
}