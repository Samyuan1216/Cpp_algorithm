/*
 * @lc app=leetcode.cn id=1434 lang=cpp
 *
 * [1434] 每个人戴不同帽子的方案数
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    const int MOD = 1000000007;
    int numberWays(vector<vector<int>>& hats)
    {
        int m = 0;
        for (auto &person: hats)
        {
            for (auto &x: person)
            {
                m = max(m, x);
            }
        }

        int n = hats.size();
        vector<int> hat(m + 1);
        for (int i = 0; i < n; i++)
        {
            for (auto &x: hats[i])
            {
                hat[x] |= 1 << i;
            }
        }

        vector<vector<int>> dp(m + 1, vector<int>(1 << n, -1));
        return f(hat, m, n, 1, 0, dp);
    }

    int f(vector<int> &hat, int m, int n, int i, int s, vector<vector<int>> &dp)
    {
        if (s == (1 << n) - 1)
        {
            return 1;
        }

        if (i == m + 1)
        {
            return 0;
        }

        if (dp[i][s] != -1)
        {
            return dp[i][s];
        }

        int ans = f(hat, m, n, i + 1, s, dp);
        int cur = hat[i];

        int right = 0;
        while (cur != 0)
        {
            right = cur & -cur;
            if ((s & right) == 0)
            {
                ans = (ans + f(hat, m, n, i + 1, s | right, dp)) % MOD;
            }

            cur ^= right;
        }

        dp[i][s] = ans;
        return ans;
    }
};
// @lc code=end

