#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n = 0, T = 0;
    cin >> n >> T;

    vector<int> a(n);
    for (auto &x: a)
    {
        cin >> x;
    }

    vector<int> b;
    while (T--)
    {
        int k = 0;
        cin >> k;

        for (int i = 0; i < k; i++)
        {
            for (int j = i; j < n; j += k)
            {
                b.push_back(a[j]);
            }
        }

        a = b;
        b.clear();
    }

    for (auto &x: a)
    {
        cout << x << " ";
    }
}