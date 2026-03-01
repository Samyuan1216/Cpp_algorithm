/*
 * @lc app=leetcode.cn id=560 lang=cpp
 *
 * [560] 和为 K 的子数组
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int subarraySum(vector<int>& nums, int k)
    {
        map<int, int> m;
        m[0] = 1;

        int ans = 0, sum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i];
            ans += m[sum - k];
            m[sum]++;
        }

        return ans;
    }
};
// @lc code=end

