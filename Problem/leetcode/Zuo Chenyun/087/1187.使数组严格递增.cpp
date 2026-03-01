/*
 * @lc app=leetcode.cn id=1187 lang=cpp
 *
 * [1187] 使数组严格递增
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2)
    {
        sort(arr2.begin(), arr2.end());
        int m = unique(arr2.begin(), arr2.end()) - arr2.begin();

        int n = arr1.size();
        vector<int> dp(n + 1);
        for (int i = n - 1, ans, pre, find; i >= 0; i--)
        {
            ans = INT32_MAX;
            pre = (i == 0? INT32_MIN: arr1[i - 1]);
            find = upper_bound(arr2.begin(), arr2.begin() + m, pre) - arr2.begin();

            for (int j = i, k = 0, ne; j <= n; j++, k++)
            {
                if (j == n)
                {
                    ans = min(ans, k);
                }
                else
                {
                    if (pre < arr1[j])
                    {
                        ne = dp[j + 1];
                        if (ne != INT32_MAX)
                        {
                            ans = min(ans, k + ne);
                        }
                    }

                    if (find < m)
                    {
                        pre = arr2[find++];
                    }
                    else
                    {
                        break;
                    }
                }
            }

            dp[i] = ans;
        }

        return (dp[0] == INT32_MAX? -1: dp[0]);
    }
};
// @lc code=end

