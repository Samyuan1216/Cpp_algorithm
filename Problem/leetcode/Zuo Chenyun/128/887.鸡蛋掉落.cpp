/*
 * @lc app=leetcode.cn id=887 lang=cpp
 *
 * [887] 鸡蛋掉落
 */

// @lc code=start
#include <bits/stdc++.h>

class Solution
{
public:
    int superEggDrop(int k, int n)
    {
        if (k == 1)
        {
            return n;
        }

        int *dp = new int[k + 1]();
        for (int j = 1; j <= n; j++)
        {
            for (int i = 1, pre = 0, tmp; i <= k; i++)
            {
                tmp = dp[i];
                dp[i] = dp[i] + pre + 1;
                pre = tmp;

                if (dp[i] >= n)
                {
                    return j;
                }
            }
        }

        return -1;
    }
};
// @lc code=end

