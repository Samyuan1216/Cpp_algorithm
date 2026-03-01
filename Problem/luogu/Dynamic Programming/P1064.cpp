#include <bits/stdc++.h>
using namespace std;

const int MAXN = 32010, MAXM = 70;
vector<int> cost(MAXM), val(MAXM), king(MAXM), fans(MAXM), dp(MAXN);
vector<vector<int>> follows(MAXM, vector<int>(2));
int n = 0, m = 0;

int main()
{
    cin >> n >> m;

    for (int i = 1, v = 0, p = 0, q = 0; i <= m; i++)
    {
        cin >> v >> p >> q;

        cost[i] = v;
        val[i] = v * p;
        king[i] = (q == 0);

        if (q != 0)
        {
            follows[q][fans[q]++] = i;
        }
    }

    for (int i = 1, fan1 = 0, fan2 = 0; i <= m; i++)
    {
        if (king[i] == 1)
        {
            for (int j = n; j >= cost[i]; j--)
            {
                dp[j] = max(dp[j], dp[j - cost[i]] + val[i]);

                fan1 = (fans[i] >= 1? follows[i][0]: -1);
                fan2 = (fans[i] >= 2? follows[i][1]: -1);

                if (fan1 != -1 && j - cost[i] - cost[fan1] >= 0)
                {
                    dp[j] = max(dp[j], dp[j - cost[i] - cost[fan1]] + val[i] + val[fan1]);
                }

                if (fan2 != -1 && j - cost[i] - cost[fan2] >= 0)
                {
                    dp[j] = max(dp[j], dp[j - cost[i] - cost[fan2]] + val[i] + val[fan2]);
                }

                if (fan1 != -1 && fan2 != -1 && j - cost[i] - cost[fan1] - cost[fan2] >= 0)
                {
                    dp[j] = max(dp[j], dp[j - cost[i] - cost[fan1] - cost[fan2]] + val[i] + val[fan1] + val[fan2]);
                }
            }
        }
    }

    cout << dp[n] << endl;
}