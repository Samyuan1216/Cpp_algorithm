/*
 * @lc app=leetcode.cn id=1851 lang=cpp
 *
 * [1851] 包含每个查询的最小区间
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    struct data
    {
        int len;
        int index;

        data(int a, int b): len(a), index(b) {}

        bool operator<(const data &other) const
        {
            return this->len > other.len;
        }
    };
    
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries)
    {
        int n = intervals.size(), m = queries.size();
        sort(intervals.begin(), intervals.end(), [](auto &a, auto &b)
        {
            return a[0] < b[0];
        });
        
        vector<vector<int>> arr(m, vector<int>(2));
        for (int i = 0; i < m; i++)
        {
            arr[i][0] = queries[i];
            arr[i][1] = i;
        }

        sort(arr.begin(), arr.end(), [](auto &a, auto &b)
        {
            return a[0] < b[0];
        });

        priority_queue<data> heap;
        vector<int> ans(m);
        for (int i = 0, j = 0; i < m; i++)
        {
            for (; j < n && intervals[j][0] <= arr[i][0]; j++)
            {
                heap.push(data(intervals[j][1] - intervals[j][0] + 1, intervals[j][1]));
            }

            while (!heap.empty() && heap.top().index < arr[i][0])
            {
                heap.pop();
            }

            if (!heap.empty())
            {
                ans[arr[i][1]] = heap.top().len;
            }
            else
            {
                ans[arr[i][1]] = -1;
            }
        }

        return ans;
    }
};
// @lc code=end

