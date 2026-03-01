/*
 * @lc app=leetcode.cn id=179 lang=cpp
 *
 * [179] 最大数
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string largestNumber(vector<int>& nums)
    {
        int n = nums.size();
        vector<string> numstr(n);

        for (int i = 0; i < n; i++)
        {
            numstr[i] = to_string(nums[i]);
        }

        sort(numstr.begin(), numstr.end(), [](string &a, string &b)
        {
            return a + b > b + a;
        });

        if (numstr[0] == "0")
        {
            return "0";
        }

        string ans;
        for (auto &s: numstr)
        {
            ans += s;
        }

        return ans;
    }
};
// @lc code=end

