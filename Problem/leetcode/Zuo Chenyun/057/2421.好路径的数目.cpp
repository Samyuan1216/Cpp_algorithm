/*
 * @lc app=leetcode.cn id=2421 lang=cpp
 *
 * [2421] 好路径的数目
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges)
    {
        int n = vals.size();
        sort(edges.begin(), edges.end(), [&vals](vector<int> &a, vector<int> &b)
        {
            return max(vals[a[0]], vals[a[1]]) < max(vals[b[0]], vals[b[1]]);
        });

        vector<int> father(n), maxcnt(n);
        for (int i = 0; i < n; i++)
        {
            father[i] = i;
            maxcnt[i] = 1;
        }

        function<int (int)> find = [&](int i) -> int
        {
            if (i != father[i])
            {
                father[i] = find(father[i]);
            }

            return father[i];
        };

        auto un = [&](int a, int b) -> int
        {
            int ua = find(a), ub = find(b);
            int path = 0;

            if (vals[ua] > vals[ub])
            {
                father[ub] = ua;
            }
            else if (vals[ua] < vals[ub])
            {
                father[ua] = ub;
            }
            else
            {
                path = maxcnt[ua] * maxcnt[ub];
                father[ub] = ua;
                maxcnt[ua] += maxcnt[ub];
            }

            return path;
        };

        int ans = n;
        for (auto &edge: edges)
        {
            ans += un(edge[0], edge[1]);
        }

        return ans;
    }
};
// @lc code=end

