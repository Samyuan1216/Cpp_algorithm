/*
 * @lc app=leetcode.cn id=1590 lang=cpp
 *
 * [1590] 使数组和能被 P 整除
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minSubarray(vector<int>& nums, int p)
    {
        int mod = 0;
        for (auto &x: nums)
        {
            mod = (mod + x) % p;
        }

        if (mod == 0)
        {
            return 0;
        }

        map<int, int> m;
        m.insert(make_pair(0, -1));

        int ans = INT_MAX;
        for (int i = 0, cur = 0, find = 0; i < nums.size(); i++)
        {
            cur = (cur + nums[i]) % p;
            find = (cur + p - mod) % p;

            if (m.find(find) != m.end())
            {
                ans = min(ans, i - m[find]);
            }

            m[cur] = i;
        }

        return (ans == nums.size()? -1: ans);
    }
};
// @lc code=end

