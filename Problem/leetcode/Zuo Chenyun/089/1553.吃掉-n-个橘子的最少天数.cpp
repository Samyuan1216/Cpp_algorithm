/*
 * @lc app=leetcode.cn id=1553 lang=cpp
 *
 * [1553] 吃掉 N 个橘子的最少天数
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

unordered_map<int, int> dp;

class Solution
{
public:
    int minDays(int n)
    {
        if (n <= 1)
        {
            return n;
        }

        if (dp.find(n) != dp.end())
        {
            return dp[n];
        }

        int ans = min(n % 2 + 1 + minDays(n / 2), n % 3 + 1 + minDays(n / 3));
        dp[n] = ans;

        return ans;
    }
};
// @lc code=end

