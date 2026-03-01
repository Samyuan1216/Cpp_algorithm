#include <bits/stdc++.h>
using namespace std;

const int MAXM = 10010, MAXT = 10000010;
vector<long long> cost(MAXM), val(MAXM), dp(MAXT);
int t = 0, m = 0;

int main()
{
    cin >> t >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> cost[i] >> val[i];
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = cost[i]; j <= t; j++)
        {
            dp[j] = max(dp[j], dp[j - cost[i]] + val[i]);
        }
    }

    cout << dp[t] << endl;
}