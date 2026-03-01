/*
 * @lc app=leetcode.cn id=851 lang=cpp
 *
 * [851] 喧闹和富有
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet)
    {
        int n = quiet.size(), m = richer.size();

        vector<int> head(n), next(m + 1), to(m + 1), indegree(n);
        int cnt = 1;
        for (auto &person: richer)
        {
            next[cnt] = head[person[0]];
            to[cnt] = person[1];
            head[person[0]] = cnt++;

            indegree[person[1]]++;
        }

        vector<int> q(n);
        int l = 0, r = 0;
        for (int i = 0; i < n; i++)
        {
            if (indegree[i] == 0)
            {
                q[r++] = i;
            }
        }

        vector<int> ans(n);
        for (int i = 0; i < n; i++)
        {
            ans[i] = i;
        }

        while (l < r)
        {
            int cur = q[l++];
            for (int i = head[cur]; i > 0; i = next[i])
            {
                if (quiet[ans[cur]] < quiet[ans[to[i]]])
                {
                    ans[to[i]] = ans[cur];
                }

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

