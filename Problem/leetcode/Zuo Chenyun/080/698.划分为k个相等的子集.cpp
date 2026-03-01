/*
 * @lc app=leetcode.cn id=698 lang=cpp
 *
 * [698] 划分为k个相等的子集
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool canPartitionKSubsets1(vector<int>& nums, int k)
    {
        int sum = 0;
        for (auto &x: nums)
        {
            sum += x;
        }

        if (sum % k != 0)
        {
            return false;
        }

        int n = nums.size();
        vector<int> dp(1 << n);
        
        return f1(nums, sum / k, (1 << n) - 1, 0, k, dp);
    }

    bool f1(vector<int> &nums, int limit, int status, int cur, int rest, vector<int> &dp)
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
                    ans = f1(nums, limit, status ^ (1 << i), 0, rest - 1, dp);
                }
                else
                {
                    ans = f1(nums, limit, status ^ (1 << i), cur + nums[i], rest, dp);
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

    bool canPartitionKSubsets(vector<int>& nums, int k)
    {
        int sum = 0;
        for (auto &x: nums)
        {
            sum += x;
        }

        if (sum % k != 0)
        {
            return false;
        }

        int n = nums.size();
        sort(nums.begin(), nums.end());

        vector<int> group(k);
        return f(group, sum / k, nums, n - 1);
    }

    bool f(vector<int> &group, int target, vector<int> &nums, int index)
    {
        if (index < 0)
        {
            return true;
        }

        int num = nums[index];
        for (int i = 0; i < group.size(); i++)
        {
            if (group[i] + num <= target)
            {
                group[i] += num;
                if (f(group, target, nums, index - 1))
                {
                    return true;
                }

                group[i] -= num;
                while (i + 1 < group.size() && group[i] == group[i + 1])
                {
                    i++;
                }
            }
        }

        return false;
    }
};
// @lc code=end

