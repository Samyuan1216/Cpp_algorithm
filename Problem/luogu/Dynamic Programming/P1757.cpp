#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010, MAXM = 1010;
vector<vector<int>> bag(MAXN, vector<int>(3));
vector<int> dp(MAXM);
int n = 0, m = 0;

int main()
{
    cin >> m >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> bag[i][0] >> bag[i][1] >> bag[i][2];
    }

    sort(bag.begin() + 1, bag.begin() + n + 1, [](vector<int> &a, vector<int> &b)\
    {
        return a[2] < b[2];
    });

    for (int start = 1, end = 2; start <= n;)
    {
        while (end <= n && bag[end][2] == bag[start][2])
        {
            end++;
        }

        for (int j = m; j >= 0; j--)
        {
            for (int k = start; k < end; k++)
            {
                if (j - bag[k][0] >= 0)
                {
                    dp[j] = max(dp[j], dp[j - bag[k][0]] + bag[k][1]);
                }
            }
        }

        start = end++;
    }

    cout << dp[m] << endl;
}