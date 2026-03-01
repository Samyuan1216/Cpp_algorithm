#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

const int MAXN = 250;
vvi dp(MAXN, vi(MAXN, -1));
vi diff(MAXN);
int n, maxn;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> diff[i];

        dp[i][i] = diff[i];
        maxn = max(maxn, diff[i]);
    }

    for (int l = n - 2; l >= 0; l--)
    {
        for (int r = l + 1; r < n; r++)
        {
            for (int m = l; m < r; m++)
            {
                if (dp[l][m] == dp[m + 1][r])
                {
                    dp[l][r] = max(dp[l][r], dp[l][m] + 1);
                }
            }

            maxn = max(maxn, dp[l][r]);
        }
    }

    cout << maxn << endl;
}