#include <bits/stdc++.h>
using namespace std;

vector<int> diff(110);
int n, k, x, cnt, idx;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> diff[i];
    }

    cin >> k >> x;
    for (int i = 0; i < n; i++)
    {
        if (diff[i] == x)
        {
            cnt++;
        }

        if (cnt == k)
        {
            idx = i + 1;
            break;
        }
    }

    if (cnt == k)
    {
        cout << idx << endl;
    }
    else
    {
        cout << "Error" << endl;
    }
}