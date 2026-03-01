/*
 * @lc app=leetcode.cn id=45 lang=cpp
 *
 * [45] 跳跃游戏 II
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int jump(vector<int>& nums)
    {
        int n = nums.size();

        int cur = 0, next = 0, ans = 0;
        for (int i = 0; i < n; i++)
        {
            if (cur < i)
            {
                ans++;
                cur = next;
            }

            next = max(next, i + nums[i]);
        }

        return ans;
    }
};
// @lc code=end

