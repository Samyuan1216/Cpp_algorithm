/*
 * @lc app=leetcode.cn id=123 lang=cpp
 *
 * [123] 买卖股票的最佳时机 III
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxProfit1(vector<int>& prices)
    {
        int n = prices.size();
        vector<int> dp1(n);
        for (int i = 1, minn = prices[0]; i < n; i++)
        {
            minn = min(minn, prices[i]);
            dp1[i] = max(dp1[i - 1], prices[i] - minn);
        }

        vector<int> best(n);
        best[0] = dp1[0] - prices[0];
        for (int i = 1; i < n; i++)
        {
            best[i] = max(best[i - 1], dp1[i] - prices[i]);
        }

        int ans = 0;
        vector<int> dp2(n);
        for (int i = 1; i < n; i++)
        {
            dp2[i] = best[i] + prices[i];
            ans = max(ans, dp2[i]);
        }

        return ans;
    }

    int maxProfit(vector<int>& prices)
    {
        int dp1 = 0, best = -prices[0], ans = 0;
        for (int i = 1, minn = prices[0]; i < prices.size(); i++)
        {
            minn = min(minn, prices[i]);
            dp1 = max(dp1, prices[i] - minn);
            best = max(best, dp1 - prices[i]);
            ans = max(ans, best + prices[i]);
        }

        return ans;
    }
};
// @lc code=end

