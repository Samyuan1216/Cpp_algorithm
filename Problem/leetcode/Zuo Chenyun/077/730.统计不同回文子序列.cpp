/*
 * @lc app=leetcode.cn id=730 lang=cpp
 *
 * [730] 统计不同回文子序列
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int countPalindromicSubsequences(string s)
    {
        int n = s.length();
        int mod = 1000000007;

        vector<int> last(256);

        vector<int> left(n);
        fill(last.begin(), last.end(), -1);
        for (int i = 0; i < n; i++)
        {
            left[i] = last[s[i]];
            last[s[i]] = i;
        }

        vector<int> right(n);
        fill(right.begin(), right.end(), n);
        for (int i = n - 1; i >= 0; i--)
        {
            right[i] = last[s[i]];
            last[s[i]] = i;
        }

        vector<vector<long long>> dp(n, vector<long long>(n));
        for (int i = 0; i < n; i++)
        {
            dp[i][i] = 1;
        }

        for (int i = n - 2; i >= 0; i--)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (s[i] != s[j])
                {
                    dp[i][j] = dp[i][j - 1] + dp[i + 1][j] - dp[i + 1][j - 1] + mod;
                }
                else
                {
                    int l = right[i];
                    int r = left[j];

                    if (l > r)
                    {
                        dp[i][j] = 2 * dp[i + 1][j - 1] + 2;
                    }
                    else if (l == r)
                    {
                        dp[i][j] = 2 * dp[i + 1][j - 1] + 1;
                    }
                    else
                    {
                        dp[i][j] = 2 * dp[i + 1][j - 1] - dp[l + 1][r - 1] + mod;
                    }
                }

                dp[i][j] %= mod;
            }
        }

        return dp[0][n - 1];
    }
};
// @lc code=end

