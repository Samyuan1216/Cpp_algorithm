#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n = 0, m = 0;
    cin >> n >> m;

    vector<int> a(n);
    for (auto &x: a)
    {
        cin >> x;
    }

    while (m--)
    {
        int x = 0;
        cin >> x;

        auto iter = lower_bound(a.begin(), a.end(), x);
        if (x == *iter)
        {
            cout << iter - a.begin() + 1 << " ";
        }
        else
        {
            cout << "-1" << " ";
        }
    }
}