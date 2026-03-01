/*
 * @lc app=leetcode.cn id=2050 lang=cpp
 *
 * [2050] 并行课程 III
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time)
    {
        int m = relations.size();
        vector<int> head(n + 1), next(m + 1), to(m + 1), indegree(n + 1);
        int cnt = 1;

        for (auto &courses: relations)
        {
            next[cnt] = head[courses[0]];
            to[cnt] = courses[1];
            head[courses[0]] = cnt++;

            indegree[courses[1]]++;
        }

        vector<int> q(n + 1);
        int l = 0, r = 0;
        for (int i = 1; i <= n; i++)
        {
            if (indegree[i] == 0)
            {
                q[r++] = i;
            }
        }

        vector<int> cost(n + 1);
        int ans = 0;
        while (l < r)
        {
            int cur = q[l++];
            cost[cur] += time[cur - 1];
            ans = max(ans, cost[cur]);

            for (int i = head[cur]; i > 0; i = next[i])
            {
                cost[to[i]] = max(cost[to[i]], cost[cur]);

                indegree[to[i]]--;
                if (indegree[to[i]] == 0)
                {
                    q[r++] = to[i];
                }
            }
        }

        return ans;
    }
};
// @lc code=end

