/*
 * @lc app=leetcode.cn id=2289 lang=cpp
 *
 * [2289] 使数组按非递减顺序排列
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int totalSteps(vector<int>& nums)
    {
        int n = nums.size();
        vector<vector<int>> st(n, vector<int>(2));
        int r = -1;

        int ans = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            int round = 0;
            while (r >= 0 && nums[i] > st[r][0])
            {
                round = max(round + 1, st[r--][1]);
            }

            st[++r][0] = nums[i];
            st[r][1] = round;
            ans = max(ans, round);
        }

        return ans;
    }
};
// @lc code=end

