/*
 * @lc app=leetcode.cn id=1665 lang=cpp
 *
 * [1665] 完成所有任务的最少初始能量
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minimumEffort(vector<vector<int>>& tasks)
    {
        sort(tasks.begin(), tasks.end(), [](vector<int> &a, vector<int> &b)
        {
            return (a[0] - a[1]) > (b[0] - b[1]);
        });

        int ans = 0;
        for (auto &task: tasks)
        {
            ans = max(task[1], ans + task[0]);
        }

        return ans;
    }
};
// @lc code=end

