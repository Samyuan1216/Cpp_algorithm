/*
 * @lc app=leetcode.cn id=1655 lang=cpp
 *
 * [1655] 分配重复整数
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity)
    {
        sort(nums.begin(), nums.end());

        int n = 1;
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] != nums[i - 1])
            {
                n++;
            }
        }

        vector<int> cnt(n);
        int c = 1;
        for (int i = 1, j = 0; i < nums.size(); i++)
        {
            if (nums[i] != nums[i - 1])
            {
                cnt[j++] = c;
                c = 1;
            }
            else
            {
                c++;
            }
        }
        cnt[n - 1] = c;

        int m = quantity.size();
        vector<int> sum(1 << m);
        for (int i = 0, v, h; i < m; i++)
        {
            v = quantity[i];
            h = 1 << i;

            for (int j = 0; j < h; j++)
            {
                sum[h | j] = sum[j] + v;
            }
        }

        vector<vector<int>> dp(1 << m, vector<int>(n));
        return f(cnt, sum, (1 << m) - 1, 0, dp);
    }

    bool f(vector<int> &cnt, vector<int> &sum, int status, int index, vector<vector<int>> &dp)
    {
        if (status == 0)
        {
            return true;
        }

        if (index == cnt.size())
        {
            return false;
        }

        if (dp[status][index] != 0)
        {
            return dp[status][index] == 1;
        }

        bool ans = false;
        int k = cnt[index];
        for (int j = status; j > 0; j = (j - 1) & status)
        {
            if (sum[j] <= k && f(cnt, sum, status ^ j, index + 1, dp))
            {
                ans = true;
                break;
            }
        }

        if (!ans)
        {
            ans = f(cnt, sum, status, index + 1, dp);
        }

        dp[status][index] = (ans? 1: -1);
        return ans;
    }
};
// @lc code=end

