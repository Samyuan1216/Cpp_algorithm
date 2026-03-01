#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;

const int MAXN = 210;
vvvi dp(MAXN, vvi(MAXN, vi(2)));
vi diff(MAXN), sum(MAXN);
int n, minn = INT32_MAX, maxn = INT32_MIN;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> diff[i];
        sum[i + 1] = diff[i] + sum[i];
    }

    for (int i = n; i < 2 * n; i++)
    {
        sum[i + 1] = diff[i - n] + sum[i];
    }

    for (int l = 0; l < 2 * n; l++)
    {
        for (int r = 0; r < 2 * n; r++)
        {
            dp[l][r][0] = INT32_MAX;
            dp[l][r][1] = INT32_MIN;
        }
    }

    for (int i = 0; i < 2 * n; i++)
    {
        dp[i][i][0] = dp[i][i][1] = 0;
    }

    for (int l = 2 * n - 2; l >= 0; l--)
    {
        for (int r = l + 1; r < 2 * n; r++)
        {
            for (int m = l; m < r; m++)
            {
                dp[l][r][0] = min(dp[l][r][0], dp[l][m][0] + dp[m + 1][r][0] + (sum[r + 1] - sum[l]));
                dp[l][r][1] = max(dp[l][r][1], dp[l][m][1] + dp[m + 1][r][1] + (sum[r + 1] - sum[l]));
            }
        }
    }

    for (int l = 0, r = n - 1; l < n; l++, r++)
    {
        minn = min(minn, dp[l][r][0]);
        maxn = max(maxn, dp[l][r][1]);
    }

    cout << minn << endl;
    cout << maxn << endl;
}