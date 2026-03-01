/*
 * @lc app=leetcode.cn id=907 lang=cpp
 *
 * [907] 子数组的最小值之和
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int sumSubarrayMins(vector<int>& arr)
    {
        const int MOD = 1000000007;
        int n = arr.size(), r = -1;
        long long ans = 0;
        vector<int> s(n);

        for (int i = 0; i < n; i++)
        {
            while (r >= 0 && arr[s[r]] >= arr[i])
            {
                int cur = s[r--];
                int left = (r == -1? -1: s[r]);
                ans = (ans + (long long)(cur - left) * (i - cur) * arr[cur]) % MOD;
            }

            s[++r] = i;
        }

        while (r >= 0)
        {
            int cur = s[r--];
            int left = (r == -1? -1: s[r]);
            ans = (ans + (long long)(cur - left) * (n - cur) * arr[cur]) % MOD;
        }

        return ans;
    }
};
// @lc code=end

