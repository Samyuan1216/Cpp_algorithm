/*
 * @lc app=leetcode.cn id=936 lang=cpp
 *
 * [936] 戳印序列
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> movesToStamp(string stamp, string target)
    {
        int n = target.length(), m = stamp.length();
        vector<int> indegree(n - m + 1, m);

        vector<int> head(n), next(n * n), to(n * n), q(n - m + 1);
        int cnt = 1, l = 0, r = 0;
        for (int i = 0; i <= n - m; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (target[i + j] == stamp[j])
                {
                    indegree[i]--;
                    if (indegree[i] == 0)
                    {
                        q[r++] = i;
                    }
                }
                else
                {
                    next[cnt] = head[i + j];
                    to[cnt] = i;
                    head[i + j] = cnt++;
                }
            }
        }

        vector<int> visited(n), path(n - m + 1);
        int size = 0;
        while (l < r)
        {
            int cur = q[l++];
            path[size++] = cur;

            for (int i = 0; i < m; i++)
            {
                if (visited[cur + i] == 0)
                {
                    visited[cur + i] = 1;
                    for (int j = head[cur + i]; j > 0; j = next[j])
                    {
                        indegree[to[j]]--;
                        if (indegree[to[j]] == 0)
                        {
                            q[r++] = to[j];
                        }
                    }
                }
            }
        }

        if (size != n - m + 1)
        {
            return vector<int>();
        }

        for (int i = 0, j = size - 1; i < j; i++, j--)
        {
            swap(path[i], path[j]);
        }

        return path;
    }
};
// @lc code=end

