/*
 * @lc app=leetcode.cn id=739 lang=cpp
 *
 * [739] 每日温度
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> dailyTemperatures(vector<int>& temperatures)
    {
        int n = temperatures.size();
        vector<int> ans(n), s(n);
        int r = -1;

        int cur = 0;
        for (int i = 0; i < n; i++)
        {
            while (r >= 0 && temperatures[s[r]] <= temperatures[i])
            {
                cur = s[r--];
                ans[cur] = i;
            }

            s[++r] = i;
        }

        while (r >= 0)
        {
            cur = s[r--];
            ans[cur] = -1;
        }

        for (int i = n - 2; i >= 0; i--)
        {
            if (ans[i] != -1 && temperatures[ans[i]] == temperatures[i])
            {
                ans[i] = ans[ans[i]];
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (ans[i] == -1)
            {
                ans[i] = 0;
            }
            else
            {
                ans[i] -= i;
            }
        }

        return ans;
    }
};
// @lc code=end

