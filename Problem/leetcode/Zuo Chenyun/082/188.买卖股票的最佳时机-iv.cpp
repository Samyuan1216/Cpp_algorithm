/*
 * @lc app=leetcode.cn id=188 lang=cpp
 *
 * [188] 买卖股票的最佳时机 IV
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxProfit(int k, vector<int>& prices)
    {
        int n = prices.size();
        if (k >= n / 2)
        {
            return free(prices);
        }

        vector<int> dp(n);
        for (int i = 1, tmp, best; i <= k; i++)
        {
            best = dp[0] - prices[0];
            for (int j = 1; j < n; j++)
            {
                tmp = dp[j];
                dp[j] = max(dp[j - 1], best + prices[j]);
                best = max(best, tmp - prices[j]);
            }
        }

        return dp[n - 1];
    }

    int free(vector<int> &prices)
    {
        int ans = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            ans += max(0, prices[i] - prices[i - 1]);
        }

        return ans;
    }
};
// @lc code=end

