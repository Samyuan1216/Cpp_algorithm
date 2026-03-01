/*
 * @lc app=leetcode.cn id=309 lang=cpp
 *
 * [309] 买卖股票的最佳时机含冷冻期
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxProfit(vector<int>& prices)
    {
        int n = prices.size();
        if (n < 2)
        {
            return 0;
        }

        int prepare = max(-prices[0], -prices[1]);
        int done1 = max(0, prices[1] - prices[0]),done2 = 0;
        for (int i = 2, curdone; i < n; i++)
        {
            curdone = max(done1, prepare + prices[i]);
            prepare = max(prepare, done2 - prices[i]);
            done2 = done1;
            done1 = curdone;
        }

        return done1;
    }
};
// @lc code=end

