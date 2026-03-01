#include <bits/stdc++.h>
using namespace std;

vector<string> ma(100010);
int n, m, cur;

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> ma[i];
    }

    for (int i = 0; i < m; i++)
    {
        int j = n - 1;
        while (j >= 0 && ma[j][i] != '.')
        {
            j--;
        }

        cur = j;
        for (j; j >= 0; j--)
        {
            if (ma[j][i] == '-')
            {
                while (j >= 0 && ma[j][i] != '.')
                {
                    j--;
                }
                cur = j;
            }
            else if (ma[j][i] >= 'A' && ma[j][i] <= 'Z')
            {
                swap(ma[cur][i], ma[j][i]);
                cur--;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << ma[i] << endl;
    }
}