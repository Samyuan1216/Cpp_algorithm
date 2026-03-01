/*
 * @lc app=leetcode.cn id=474 lang=cpp
 *
 * [474] 一和零
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
    int zero = 0;
    int one = 0;
public:
    void zero_and_one(string s)
    {
        zero = 0, one = 0;

        for (auto &c: s)
        {
            if (c == '0')
            {
                zero++;
            }
            else
            {
                one++;
            }
        }
    }

    int findMaxForm1(vector<string>& strs, int m, int n)
    {
        int len = strs.size();
        vector<vector<vector<int>>> dp(len + 1, vector<vector<int>>(m + 1, vector<int>(n + 1)));

        for (int i = len - 1; i >= 0; i--)
        {
            zero_and_one(strs[i]);
            for (int z = 0, p1 = 0, p2 = 0; z <= m; z++)
            {
                for (int o = 0; o <= n; o++)
                {
                    p1 = dp[i + 1][z][o];
                    p2 = 0;

                    if (zero <= z && one <= o)
                    {
                        p2 = 1 + dp[i + 1][z - zero][o - one];
                    }

                    dp[i][z][o] = max(p1, p2);
                }
            }
        }

        return dp[0][m][n];
    }

    int findMaxForm(vector<string>& strs, int m, int n)
    {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (string s: strs)
        {
            zero_and_one(s);
            for (int z = m; z >= zero; z--)
            {
                for (int o = n; o >= one; o--)
                {
                    dp[z][o] = max(dp[z][o], 1 + dp[z - zero][o - one]);
                }
            }
        }

        return dp[m][n];
    }
};
// @lc code=end

