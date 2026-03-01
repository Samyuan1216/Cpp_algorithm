/*
 * @lc app=leetcode.cn id=2127 lang=cpp
 *
 * [2127] 参加会议的最多员工数
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maximumInvitations(vector<int>& favorite)
    {
        int n = favorite.size();
        vector<int> indegree(n);
        for (int i = 0; i < n; i++)
        {
            indegree[favorite[i]]++;
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

        vector<int> deep(n);
        while (l < r)
        {
            int cur = q[l++];
            int next = favorite[cur];
            deep[next] = max(deep[next], deep[cur] + 1);

            indegree[next]--;
            if (indegree[next] == 0)
            {
                q[r++] = next;
            }
        }

        int small_ring = 0, big_ring = 0;
        for (int i = 0; i < n; i++)
        {
            if (indegree[i] > 0)
            {
                int max_size = 1;
                indegree[i] = 0;

                for (int j = favorite[i]; j != i; j = favorite[j])
                {
                    max_size++;
                    indegree[j] = 0;
                }

                if (max_size == 2)
                {
                    small_ring += 2 + deep[i] + deep[favorite[i]];
                }
                else
                {
                    big_ring = max(big_ring, max_size);
                }
            }
        }

        return max(small_ring, big_ring);
    }
};
// @lc code=end

