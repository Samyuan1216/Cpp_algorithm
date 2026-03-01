#include <bits/stdc++.h>

using ll = long long;

const int MAXN = 10, MAXK = 100;
ll dp[MAXN][1 << MAXN][2][MAXK];
int n, kings, maxs;

int get(int s, int j)
{
    return (s >> j) & 1;
}

int set(int s, int j, int v)
{
    return (v == 0? s & (~(1 << j)): s | (1 << j));
}

int main()
{
    std::cin >> n >> kings;
    maxs = 1 << n;

    for (int s = 0; s < maxs; s++)
    {
        for (int k = 0; k <= kings; k++)
        {
            dp[0][s][0][k] = (k == 0? 1: 0);
        }
    }

    for (int i = n - 1; i >= 0; i--)
    {
        for (int s = 0; s < maxs; s++)
        {
            for (int k = 0; k <= kings; k++)
            {
                dp[n][s][0][k] = dp[n][s][1][k] = dp[0][s][0][k];
            }
        }

        for (int j = n - 1; j >= 0; j--)
        {
            for (int s = 0; s < maxs; s++)
            {
                for (int leftup = 0; leftup <= 1; leftup++)
                {
                    for (int k = 0; k <= kings; k++)
                    {
                        int left = (j == 0? 0: get(s, j - 1));
                        int up = get(s, j), rightup = get(s, j + 1);

                        ll ans = dp[j + 1][set(s, j, 0)][up][k];
                        if (k > 0 && left == 0 && leftup == 0 && up == 0 && rightup == 0)
                        {
                            ans += dp[j + 1][set(s, j, 1)][up][k - 1];
                        }

                        dp[j][s][leftup][k] = ans;
                    }
                }
            }
        }
    }

    std::cout << dp[0][0][0][kings] << std::endl;
}