#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110, MAXH = 55010;
vector<int> cost(MAXN), val(MAXN), dp(MAXH, INT32_MAX);
int n = 0, h = 0, maxv = 0, m = 0, ans = INT32_MAX;

int main()
{
    cin >> n >> h;
    for (int i = 1; i <= n; i++)
    {
        cin >> cost[i] >> val[i];

        maxv = max(maxv, cost[i]);
    }

    m = h + maxv;
    dp[0] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = cost[i]; j <= m; j++)
        {
            if (dp[j - cost[i]] != INT32_MAX)
            {
                dp[j] = min(dp[j], dp[j - cost[i]] + val[i]);
            }
        }
    }

    for (int i = h; i <= m; i++)
    {
        ans = min(ans, dp[i]);
    }

    cout << ans << endl;
}