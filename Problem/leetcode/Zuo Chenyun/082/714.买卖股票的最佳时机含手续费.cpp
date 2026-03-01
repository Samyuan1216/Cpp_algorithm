/*
 * @lc app=leetcode.cn id=714 lang=cpp
 *
 * [714] 买卖股票的最佳时机含手续费
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxProfit(vector<int>& prices, int fee)
    {
        int prepare = -prices[0] - fee;
        int done = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            done = max(done, prepare + prices[i]);
            prepare = max(prepare, done - prices[i] - fee);
        }

        return done;
    }
};
// @lc code=end

