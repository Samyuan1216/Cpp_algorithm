/*
 * @lc app=leetcode.cn id=210 lang=cpp
 *
 * [210] 课程表 II
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites)
    {
        int m = prerequisites.size();
        vector<int> indegree(numCourses);

        vector<int> head(numCourses);
        vector<int> next(m + 1);
        vector<int> to(m + 1);
        int cnt = 1;
        for (auto &edge: prerequisites)
        {
            next[cnt] = head[edge[1]];
            to[cnt] = edge[0];
            head[edge[1]] = cnt++;

            indegree[edge[0]]++;
        }

        vector<int> q(numCourses);
        int l = 0, r = 0;
        for (int i = 0; i < numCourses; i++)
        {
            if (indegree[i] == 0)
            {
                q[r++] = i;
            }
        }

        int cnt2 = 0;
        while (l < r)
        {
            int cur = q[l++];
            cnt2++;

            for (int i = head[cur]; i > 0; i = next[i])
            {
                indegree[to[i]]--;
                if (indegree[to[i]] == 0)
                {
                    q[r++] = to[i];
                }
            }
        }

        return (cnt2 == numCourses? q: vector<int>());
    }
};
// @lc code=end

