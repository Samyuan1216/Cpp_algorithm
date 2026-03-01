/*
 * @lc app=leetcode.cn id=1687 lang=cpp
 *
 * [1687] 从仓库到码头运输箱子
 */

// @lc code=start
#include <bits/stdc++.h>

using vi = std::vector<int>;
using vvi = std::vector<vi>;

class Solution
{
public:
    int boxDelivering(vvi &boxes, int portsCount, int maxBoxes, int maxWeight)
    {
        int n = boxes.size();
        vi dp(n + 1);
        dp[1] = 2;

        int weight = boxes[0][1], trip = 2;
        for (int l = 0, r = 1; r < n; r++)
        {
            weight += boxes[r][1];
            if (boxes[r][0] != boxes[r - 1][0])
            {
                trip++;
            }

            while (r - l + 1 > maxBoxes || weight > maxWeight || dp[l] == dp[l + 1])
            {
                weight -= boxes[l++][1];
                if (boxes[l][0] != boxes[l - 1][0])
                {
                    trip--;
                }
            }

            dp[r + 1] = dp[l] + trip;
        }

        return dp[n];
    }
};
// @lc code=end

