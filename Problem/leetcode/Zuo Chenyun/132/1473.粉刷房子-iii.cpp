/*
 * @lc app=leetcode.cn id=1473 lang=cpp
 *
 * [1473] 粉刷房子 III
 */

// @lc code=start
#include <bits/stdc++.h>

using vi = std::vector<int>;
using vvi = std::vector<vi>;

const int MAXN = 110, MAXC = 25, NA = INT32_MAX;
int house[MAXN], cost[MAXN][MAXC];
int n, t, c;

class Solution
{
public:
    int minCost(vi &houses, vvi &costs, int hsize, int csize, int tsize)
    {
        build(houses, costs, hsize, csize, tsize);

        vvi memo(t + 1, vi(c + 1)), dp(t + 1, vi(c + 1));
        for (int v = 0; v <= c; v++)
        {
            memo[0][v] = dp[0][v] = NA;
        }

        for (int j = 1; j <= t; j++)
        {
            for (int v = 0; v <= c; v++)
            {
                memo[j][v] = (j == 1? 0: NA);
            }
        }

        vi pre(c + 2), suf(c + 2);
        pre[0] = suf[c + 1] = NA;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= t; j++)
            {
                for (int v = 1; v <= c; v++)
                {
                    pre[v] = pre[v - 1];
                    if (memo[j - 1][v] != NA)
                    {
                        pre[v] = std::min(pre[v], memo[j - 1][v] + cost[i][v]);
                    }
                }

                for (int v = c; v >= 1; v--)
                {
                    suf[v] = suf[v + 1];
                    if (memo[j - 1][v] != NA)
                    {
                        suf[v] = std::min(suf[v], memo[j - 1][v] + cost[i][v]);
                    }
                }

                for (int v = 0; v <= c; v++)
                {
                    int ans = NA;
                    if (house[i] != 0)
                    {
                        if (house[i] == v)
                        {
                            ans = memo[j][house[i]];
                        }
                        else
                        {
                            ans = memo[j - 1][house[i]];
                        }
                    }
                    else
                    {
                        if (v == 0)
                        {
                            ans = suf[1];
                        }
                        else
                        {
                            ans = std::min(pre[v - 1], suf[v + 1]);
                            if (memo[j][v] != NA)
                            {
                                ans = std::min(ans, memo[j][v] + cost[i][v]);
                            }
                        }
                    }

                    dp[j][v] = ans;
                }
            }

            std::swap(dp, memo);
        }

        return (memo[t][0] == NA? -1: memo[t][0]);
    }

    void build(vi &houses, vvi &costs, int hsize, int csize, int tsize)
    {
        n = hsize, t = tsize, c = csize;
        for (int i = 1; i <= n; i++)
        {
            house[i] = houses[i - 1];
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= c; j++)
            {
                cost[i][j] = costs[i - 1][j - 1];
            }
        }

        t++;
    }
};
// @lc code=end

