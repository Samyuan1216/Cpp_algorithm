/*
 * @lc app=leetcode.cn id=3719 lang=cpp
 *
 * [3719] 最长平衡子数组 I
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int longestBalanced(vector<int>& nums)
    {
        int ans = 0, n = nums.size();
        for (int i = 0; i < n; i++)
        {
            unordered_set<int> o, e;
            for (int j = i; j < n; j++)
            {
                if (nums[j] & 1)
                {
                    e.insert(nums[j]);
                }
                else
                {
                    o.insert(nums[j]);
                }

                if (e.size() == o.size())
                {
                    ans = max(ans, j - i + 1);
                }
            }
        }

        return ans;
    }
};
// @lc code=end

