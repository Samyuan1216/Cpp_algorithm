/*
 * @lc app=leetcode.cn id=312 lang=cpp
 *
 * [312] 戳气球
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxCoins(vector<int>& nums)
    {
        int n = nums.size();

        vector<int> arr(n + 2);
        arr[0] = arr[n + 1] = 1;
        for (int i = 1; i <= n; i++)
        {
            arr[i] = nums[i - 1];
        }

        vector<vector<int>> dp(n + 2, vector<int>(n + 2));
        for (int i = 1; i <= n; i++)
        {
            dp[i][i] = arr[i - 1] * arr[i] * arr[i + 1];
        }

        for (int l = n, ans = 0; l >= 1; l--)
        {
            for (int r = l + 1; r <= n; r++)
            {
                ans = max(arr[l - 1] * arr[l] * arr[r + 1] + dp[l + 1][r], arr[l - 1] * arr[r] * arr[r + 1] + dp[l][r - 1]);
                for (int k = l + 1; k < r; k++)
                {
                    ans = max(ans, arr[l - 1] * arr[k] * arr[r + 1] + dp[l][k - 1] + dp[k + 1][r]);
                }

                dp[l][r] = ans;
            }
        }

        return dp[1][n];
    }
};
// @lc code=end

