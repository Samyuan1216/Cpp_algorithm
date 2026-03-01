/*
 * @lc app=leetcode.cn id=1353 lang=cpp
 *
 * [1353] 最多可以参加的会议数目
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxEvents(vector<vector<int>>& events)
    {
        int n = events.size();
        sort(events.begin(), events.end(), [](auto &a, auto &b)
        {
            return a[0] < b[0];
        });

        int minn = events[0][0], maxn = events[0][1];
        for (int i = 1; i < n; i++)
        {
            maxn = max(maxn, events[i][1]);
        }

        priority_queue<int, vector<int>, greater<int>> heap;
        int ans = 0;
        for (int days = minn, i = 0; days <= maxn; days++)
        {
            while (i < n && events[i][0] == days)
            {
                heap.push(events[i++][1]);
            }

            while (!heap.empty() && heap.top() < days)
            {
                heap.pop();
            }
            
            if (!heap.empty())
            {
                heap.pop();
                ans++;
            }
        }

        return ans;
    }
};
// @lc code=end

