/*
 * @lc app=leetcode.cn id=1124 lang=cpp
 *
 * [1124] 表现良好的最长时间段
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int longestWPI(vector<int>& hours)
    {
        map<int, int> m;
        m[0] = -1;

        int ans = 0, sum = 0;
        for (int i = 0; i < hours.size(); i++)
        {
            sum += (hours[i] > 8? 1: -1);
            if (sum > 0)
            {
                ans = i + 1;
            }
            else
            {
                if (m.find(sum - 1) != m.end())
                {
                    ans = max(ans, i - m[sum - 1]);
                }
            }

            if (m.find(sum) == m.end())
            {
                m[sum] = i;
            }
        }

        return ans;
    }
};
// @lc code=end

