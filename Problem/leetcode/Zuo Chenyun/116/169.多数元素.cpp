/*
 * @lc app=leetcode.cn id=169 lang=cpp
 *
 * [169] 多数元素
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int majorityElement(vector<int>& nums)
    {
        int cand = 0, hp = 0;
        for (auto &num: nums)
        {
            if (hp == 0)
            {
                cand = num;
                hp = 1;
            }
            else if (num == cand)
            {
                hp++;
            }
            else
            {
                hp--;
            }
        }

        if (hp == 0)
        {
            return -1;
        }

        hp = 0;
        for (auto &num: nums)
        {
            if (num == cand)
            {
                hp++;
            }
        }

        return (hp > nums.size() / 2? cand: -1);
    }
};
// @lc code=end

