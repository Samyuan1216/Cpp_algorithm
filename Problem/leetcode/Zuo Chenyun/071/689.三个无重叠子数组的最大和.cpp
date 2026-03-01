/*
 * @lc app=leetcode.cn id=689 lang=cpp
 *
 * [689] 三个无重叠子数组的最大和
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k)
    {
        int n = nums.size();
        vector<int> sum(n);

        for (int l = 0, r = 0, sumn = 0; r < n; r++)
        {
            sumn += nums[r];

            if (r - l + 1 == k)
            {
                sum[l] = sumn;
                sumn -= nums[l];
                l++;
            }
        }

        vector<int> prefix(n);
        for (int l = 1, r = k; r < n; l++, r++)
        {
            if (sum[l] > sum[prefix[r - 1]])
            {
                prefix[r] = l;
            }
            else
            {
                prefix[r] = prefix[r - 1];
            }
        }

        vector<int> suffix(n);
        suffix[n - k] = n - k;
        for (int l = n - k - 1; l >= 0; l--)
        {
            if (sum[l] >= sum[suffix[l + 1]])
            {
                suffix[l] = l;
            }
            else
            {
                suffix[l] = suffix[l + 1];
            }
        }

        vector<int> ans(3);
        for (int i = k, j = 2 * k - 1, p = 0, s = 0, sumn = 0, maxn = 0; j < n - k; i++, j++)
        {
            p = prefix[i - 1];
            s = suffix[j + 1];

            sumn = sum[p] + sum[i] + sum[s];
            if (sumn > maxn)
            {
                maxn = sumn;
                ans[0] = p;
                ans[1] = i;
                ans[2] = s;
            }
        }

        return ans;
    }
};
// @lc code=end

