/*
 * @lc app=leetcode.cn id=1659 lang=cpp
 *
 * [1659] 最大化网格幸福感
 */

// @lc code=start
#include <bits/stdc++.h>

const int MAXN = 6, MAXS = 730, MAXP = 7;
int dp[MAXN][MAXS][MAXP][MAXP];
int maxs;

class Solution
{
public:
    int getMaxGridHappiness(int m, int n, int introvertsCount, int extrovertsCount)
    {
        if (n < m)
        {
            std::swap(n, m);
        }

        maxs = (int)std::pow(3, m);

        for (int s = 0; s < maxs; s++)
        {
            for (int a = 0; a <= introvertsCount; a++)
            {
                for (int b = 0; b <= extrovertsCount; b++)
                {
                    dp[0][s][a][b] = 0;
                }
            }
        }
        
        for (int i = n - 1; i >= 0; i--)
        {
            for (int s = 0; s < maxs; s++)
            {
                for (int a = 0; a <= introvertsCount; a++)
                {
                    for (int b = 0; b <= extrovertsCount; b++)
                    {
                        dp[m][s][a][b] = dp[0][s][a][b];
                    }
                }
            }

            for (int j = m - 1, bit = (int)std::pow(3, m - 1); j >= 0; j--, bit /= 3)
            {
                for (int s = 0, left, up, neibour, pre; s < maxs; s++)
                {
                    left = (j == 0? 0: get(s, bit / 3));
                    up = get(s, bit);

                    neibour = 0, pre = 0;
                    if (up != 0)
                    {
                        neibour++;
                        pre += (up == 1? -30: 20);
                    }

                    if (left != 0)
                    {
                        neibour++;
                        pre += (left == 1? -30: 20);
                    }

                    for (int a = 0; a <= introvertsCount; a++)
                    {
                        for (int b = 0, ans; b <= extrovertsCount; b++)
                        {
                            ans = dp[j + 1][set(s, bit, 0)][a][b];
                            if (a > 0)
                            {
                                ans = std::max(ans, pre + 120 - neibour * 30 + dp[j + 1][set(s, bit, 1)][a - 1][b]);
                            }

                            if (b > 0)
                            {
                                ans = std::max(ans, pre + 40 + neibour * 20 + dp[j + 1][set(s, bit, 2)][a][b - 1]);
                            }

                            dp[j][s][a][b] = ans;
                        }
                    }
                }
            }
        }

        return dp[0][0][introvertsCount][extrovertsCount];
    }

    int get(int s, int bit)
    {
        return s / bit % 3;
    }

    int set(int s, int bit, int v)
    {
        return s - get(s, bit) * bit + v * bit;
    }
};
// @lc code=end

