/*
 * @lc app=leetcode.cn id=300 lang=cpp
 *
 * [300] 最长递增子序列
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int lengthOfLIS1(vector<int>& nums)
    {
        int n = nums.size();
        vector<int> dp(n, 1);

        int maxn = INT32_MIN;
        for (int i = 1; i < n; i++)
        {
            for (int j = i - 1; j >= 0; j--)
            {
                if (nums[j] < nums[i])
                {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }

            maxn = max(maxn, dp[i]);
        }

        return max(maxn, 1);
    }

    int lengthOfLIS(vector<int>& nums)
    {
        int n = nums.size();
        vector<int> ends(n);
        ends[0] = nums[0];
        int e = 1;

        for (int i = 1; i < n; i++)
        {
            if (nums[i] > ends[e - 1])
            {
                ends[e++] = nums[i];
            }
            else
            {
                int cur = 0;
                for (int l = 0, r = e - 1, m = 0; l <= r;)
                {
                    m = l + ((r - l) >> 1);
                    if (nums[i] <= ends[m])
                    {
                        cur = m;
                        r = m - 1;
                    }
                    else
                    {
                        l = m + 1;
                    }
                }

                ends[cur] = nums[i];
            }
        }

        return e;
    }
};
// @lc code=end

