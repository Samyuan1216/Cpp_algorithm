/*
 * @lc app=leetcode.cn id=464 lang=cpp
 *
 * [464] 我能赢吗
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal)
    {
        if (desiredTotal == 0)
        {
            return true;
        }

        if (maxChoosableInteger * (1 + maxChoosableInteger) / 2 < desiredTotal)
        {
            return false;
        }

        vector<int> dp(1 << (maxChoosableInteger + 1));
        return f(maxChoosableInteger, (1 << (maxChoosableInteger + 1)) - 1, desiredTotal, dp);
    }

    bool f(int n, int status, int rest, vector<int> &dp)
    {
        if (rest <= 0)
        {
            return false;
        }

        if (dp[status] != 0)
        {
            return dp[status] == 1;
        }

        bool ans = false;
        for (int i = 1; i <= n; i++)
        {
            if ((status & (1 << i)) != 0 && !f(n, (status ^ (1 << i)), rest - i, dp))
            {
                ans = true;
                break;
            }
        }

        dp[status] = (ans? 1: -1);
        return ans;
    }
};
// @lc code=end

