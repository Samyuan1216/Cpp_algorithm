/*
 * @lc app=leetcode.cn id=53 lang=cpp
 *
 * [53] 最大子数组和
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxSubArray(vector<int>& nums)
    {
        int maxn = nums[0], sum = nums[0];
        int n = nums.size();

        for (int i = 1; i < n; i++)
        {
            if (sum >= 0)
            {
                sum += nums[i];
                maxn = max(maxn, sum);
            }
            else
            {
                sum = nums[i];
                maxn = max(maxn, sum);
            }
        }

        return maxn;
    }

    // 子数组中找到拥有最大累加和的子数组
	// 并返回如下三个信息:
	// 1) 最大累加和子数组的开头left
	// 2) 最大累加和子数组的结尾right
	// 3) 最大累加和子数组的累加和sum
	// 如果不止一个子数组拥有最大累加和，那么找到哪一个都可以
    int extra(vector<int>& nums)
    {
        int maxn = nums[0], sum = nums[0], left = 0, right = 0;
        int n = nums.size();

        for (int i = 1; i < n; i++)
        {
            if (sum >= 0)
            {
                sum += nums[i];
                
                if (sum > maxn)
                {
                    maxn = sum;
                    right = i;
                }
            }
            else
            {
                sum = nums[i];
                
                if (sum > maxn)
                {
                    maxn = sum;
                    left = i;
                    right = i;
                }
            }
        }

        cout << left << " " << right << " " << endl;

        return maxn;
    }
};
// @lc code=end

