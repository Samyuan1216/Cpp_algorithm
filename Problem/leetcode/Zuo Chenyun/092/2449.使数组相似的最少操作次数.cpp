/*
 * @lc app=leetcode.cn id=2449 lang=cpp
 *
 * [2449] 使数组相似的最少操作次数
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    static bool compare(int a, int b)
    {
        if ((a & 1) == (b & 1))
        {
            return a < b;
        }

        return (a & 1) == 1;
    }

    long long makeSimilar(vector<int>& nums, vector<int>& target)
    {
        int n = nums.size();

        sort(nums.begin(), nums.end(), compare);
        sort(target.begin(), target.end(), compare);

        long long ans = 0;
        for (int i = 0; i < n; i++)
        {
            ans += abs(nums[i] - target[i]);
        }

        return ans / 4;
    }
};
// @lc code=end

