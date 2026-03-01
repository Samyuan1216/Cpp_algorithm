/*
 * @lc app=leetcode.cn id=2780 lang=cpp
 *
 * [2780] 合法分割的最小下标
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minimumIndex(vector<int>& nums)
    {
        int n = nums.size();
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

        if (hp <= n / 2)
        {
            return -1;
        }

        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] == cand)
            {
                cnt++;
            }

            if (cnt > (i + 1) / 2 && (hp - cnt) > (n - i - 1) / 2)
            {
                return i;
            }
        }

        return -1;
    }
};
// @lc code=end

