/*
 * @lc app=leetcode.cn id=473 lang=cpp
 *
 * [473] 火柴拼正方形
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool makesquare(vector<int>& matchsticks)
    {
        int sum = 0;
        for (auto &x: matchsticks)
        {
            sum += x;
        }

        if (sum % 4 != 0)
        {
            return false;
        }

        int n = matchsticks.size();
        vector<int> dp(1 << n);
        
        return f(matchsticks, sum / 4, (1 << n) - 1, 0, 4, dp);
    }

    bool f(vector<int> &nums, int limit, int status, int cur, int rest, vector<int> &dp)
    {
        if (rest == 0)
        {
            return cur == 0;
        }

        if (dp[status] != 0)
        {
            return dp[status] == 1;
        }

        bool ans = false;
        for (int i = 0; i < nums.size(); i++)
        {
            if ((status & (1 << i)) != 0 && cur + nums[i] <= limit)
            {
                if (cur + nums[i] == limit)
                {
                    ans = f(nums, limit, status ^ (1 << i), 0, rest - 1, dp);
                }
                else
                {
                    ans = f(nums, limit, status ^ (1 << i), cur + nums[i], rest, dp);
                }

                if (ans)
                {
                    break;
                }
            }
        }

        dp[status] = (ans? 1: -1);
        return ans;
    }
};
// @lc code=end

