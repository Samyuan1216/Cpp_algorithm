/*
 * @lc app=leetcode.cn id=1029 lang=cpp
 *
 * [1029] 两地调度
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int twoCitySchedCost(vector<vector<int>>& costs)
    {
        int n = costs.size();
        vector<int> m(n);

        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum += costs[i][0];
            m[i] = costs[i][1] - costs[i][0];
        }

        sort(m.begin(), m.end());

        for (int i = 0; i < n / 2; i++)
        {
            sum += m[i];
        }

        return sum;
    }
};
// @lc code=end

