/*
 * @lc app=leetcode.cn id=1326 lang=cpp
 *
 * [1326] 灌溉花园的最少水龙头数目
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minTaps(int n, vector<int>& ranges)
    {
        vector<int> right(n + 1);
        for (int i = 0, start; i <= n; i++)
        {
            start = max(0, i - ranges[i]);
            right[start] = max(right[start], i + ranges[i]);
        }

        int cur = 0, next = 0, ans = 0;
        for (int i = 0; i < n; i++)
        {
            next = max(next, right[i]);
            if (i == cur)
            {
                if (next > i)
                {
                    cur = next;
                    ans++;
                }
                else
                {
                    return -1;
                }
            }
        }

        return ans;
    }
};
// @lc code=end

