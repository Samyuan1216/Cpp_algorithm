#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 110, MAXM = 21;
vi candy(MAXN), dp(1 << MAXM, INT32_MAX), pre(1 << MAXM, INT32_MAX);
int n, m, k, t;

int main()
{
    cin >> n >> m >> k;
    for (int i = 0, status; i < n; i++)
    {
        status = 0;
        for (int j = 0; j < k; j++)
        {
            cin >> t;
            t--;
            
            status |= (1 << t);
        }

        candy[i] = status;
    }

    dp[(1 << m) - 1] = 0;

    for (int i = n - 2, tmp; i >= 0; i--)
    {
        pre = dp;
        for (int j = 0; j < ((1 << m) - 1); j++)
        {
            dp[j] = pre[j];
            if ((candy[i] | j) != j)
            {
                tmp = pre[j | candy[i]];
                if (tmp != INT32_MAX)
                {
                    dp[j] = min(dp[j], tmp + 1);
                }
            }
        }
    }

    if (dp[0] != INT32_MAX)
    {
        cout << dp[0] << endl;
    }
    else
    {
        cout << -1 << endl;
    }
}