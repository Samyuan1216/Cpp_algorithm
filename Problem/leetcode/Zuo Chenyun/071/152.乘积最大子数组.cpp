/*
 * @lc app=leetcode.cn id=152 lang=cpp
 *
 * [152] 乘积最大子数组
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxProduct(vector<int>& nums)
    {
        double ans = nums[0], minn = nums[0], maxn = nums[0], curmin = 0, curmax = 0;
        for (int i = 1; i < nums.size(); i++)
        {
            curmin = min((double)nums[i], min(minn * nums[i], maxn * nums[i]));
            curmax = max((double)nums[i], max(maxn * nums[i], minn * nums[i]));

            minn = curmin;
            maxn = curmax;

            ans = max(maxn, ans);
        }

        return (int)ans;
    }
};
// @lc code=end

