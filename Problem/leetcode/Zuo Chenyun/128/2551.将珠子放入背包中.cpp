/*
 * @lc app=leetcode.cn id=2551 lang=cpp
 *
 * [2551] 将珠子放入背包中
 */

// @lc code=start
#include <bits/stdc++.h>

class Solution
{
public:
    long long putMarbles(std::vector<int>& weights, int k)
    {
        int n = weights.size();
        std::vector<long long> split(n - 1);
        for (int i = 0; i < n - 1; i++)
        {
            split[i] = (long long)weights[i] + weights[i + 1];
        }

        sort(split.begin(), split.end());

        long long minn = 0, maxn = 0;
        for (int i = 0, j = n - 2, p = 1; p < k; i++, j--, p++)
        {
            minn += split[i];
            maxn += split[j];
        }

        return maxn - minn;
    }
};
// @lc code=end

