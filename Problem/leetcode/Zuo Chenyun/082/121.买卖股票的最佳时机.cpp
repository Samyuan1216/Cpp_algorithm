/*
 * @lc app=leetcode.cn id=121 lang=cpp
 *
 * [121] 买卖股票的最佳时机
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxProfit(vector<int>& prices)
    {
        int ans = 0;
        for (int i = 1, minn = prices[0]; i < prices.size(); i++)
        {
            minn = min(minn, prices[i]);
            ans = max(ans, prices[i] - minn);
        }

        return ans;
    }
};
// @lc code=end

