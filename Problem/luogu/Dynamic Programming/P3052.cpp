#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

const int MAXN = 20;
vvi dp(1 << MAXN, vi(MAXN, INT32_MAX));
vi cow(MAXN);
int n, w;

int main()
{
    cin >> n >> w;
    for (int i = 0; i < n; i++)
    {
        cin >> cow[i];
    }

    for (int i = 0; i < n; i++)
    {
        dp[1 << i][1] = cow[i];
    }

    for (int i = 0; i <= n; i++)
    {
        for (int s = 0; s <= (1 << n) - 1; s++)
        {
            if (dp[s][i] != INT32_MAX)
            {
                for (int k = 0; k < n; k++)
                {
                    if ((s & (1 << k)) == 0)
                    {
                        if (dp[s][i] + cow[k] <= w)
                        {
                            dp[s | (1 << k)][i] = min(dp[s | (1 << k)][i], dp[s][i] + cow[k]);
                        }
                        else
                        {
                            dp[s | (1 << k)][i + 1] = min(dp[s | (1 << k)][i + 1], cow[k]);
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i <= n; i++)
    {
        if (dp[(1 << n) - 1][i] != INT32_MAX)
        {
            cout << i << endl;
            break;
        }
    }
}