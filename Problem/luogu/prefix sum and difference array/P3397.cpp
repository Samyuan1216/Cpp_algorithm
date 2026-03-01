#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);

    int n = 0, m = 0;
    cin >> n >> m;

    vector<vector<int>> diff(n + 2, vector<int>(n + 2));
    while (m--)
    {
        int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        cin >> x1 >> y1 >> x2 >> y2;

        diff[x1][y1]++;
        diff[x1][y2 + 1]--;
        diff[x2 + 1][y1]--;
        diff[x2 + 1][y2 + 1]++;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            diff[i][j] += diff[i - 1][j] + diff[i][j - 1] - diff[i - 1][j - 1];
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << diff[i][j] << " ";
        }

        cout << endl;
    }
}