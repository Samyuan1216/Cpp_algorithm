/*
 * @lc app=leetcode.cn id=1931 lang=cpp
 *
 * [1931] 用三种不同颜色为网格涂色
 */

// @lc code=start
#include <bits/stdc++.h>

const int MAXN = 1010, MAXM = 6, MAXS = 730, MOD = 1000000007;
int dp[MAXN][MAXM][MAXS], first[MAXS];
int n, m, maxs, siz;

class Solution
{
public:
    int colorTheGrid(int rows, int cols)
    {
        build(rows, cols);

        int ans = 0;
        for (int i = 0; i < siz; i++)
        {
            ans = (ans + dfs2(1, 0, first[i], 1)) % MOD;
        }

        return ans;
    }

    void build(int rows, int cols)
    {
        n = std::max(rows, cols);
        m = std::min(rows, cols);
        maxs = std::pow(3, m);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                for (int s = 0; s < maxs; s++)
                {
                    dp[i][j][s] = -1;
                }
            }
        }

        siz = 0;
        dfs1(0, 0, 1);
    }

    void dfs1(int j, int s, int bit)
    {
        if (j == m)
        {
            first[siz++] = s;
        }
        else
        {
            int left = (j == 0? -1: get(s, bit / 3));
            if (left != 0)
            {
                dfs1(j + 1, set(s, bit, 0), bit * 3);
            }

            if (left != 1)
            {
                dfs1(j + 1, set(s, bit, 1), bit * 3);
            }

            if (left != 2)
            {
                dfs1(j + 1, set(s, bit, 2), bit * 3);
            }
        }
    }

    int dfs2(int i, int j, int s, int bit)
    {
        if (i == n)
        {
            return 1;
        }

        if (j == m)
        {
            return dfs2(i + 1, 0, s, 1);
        }

        if (dp[i][j][s] != -1)
        {
            return dp[i][j][s];
        }

        int up = get(s, bit);
        int left = (j == 0? -1: get(s, bit / 3));

        int ans = 0;
        if (up != 0 && left != 0)
        {
            ans = (ans + dfs2(i, j + 1, set(s, bit, 0), bit * 3)) % MOD;
        }

        if (up != 1 && left != 1)
        {
            ans = (ans + dfs2(i, j + 1, set(s, bit, 1), bit * 3)) % MOD;
        }

        if (up != 2 && left != 2)
        {
            ans = (ans + dfs2(i, j + 1, set(s, bit, 2), bit * 3)) % MOD;
        }

        dp[i][j][s] = ans;
        return ans;
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

