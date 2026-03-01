/*
 * @lc app=leetcode.cn id=1697 lang=cpp
 *
 * [1697] 检查边长度限制的路径是否存在
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries)
    {
        sort(edgeList.begin(), edgeList.end(), [](vector<int> a, vector<int> b)
        {
            return a[2] < b[2];
        });

        int k = queries.size();
        vector<vector<int>> questions(k, vector<int>(4));
        for (int i = 0; i < k; i++)
        {
            questions[i][0] = queries[i][0];
            questions[i][1] = queries[i][1];
            questions[i][2] = queries[i][2];
            questions[i][3] = i;
        }

        sort(questions.begin(), questions.end(), [](vector<int> a, vector<int> b)
        {
            return a[2] < b[2];
        });

        vector<int> father(n);
        for (int i = 0; i < n; i++)
        {
            father[i] = i;
        }

        function<int (int)> find = [&](int i) -> int
        {
            if (i != father[i])
            {
                father[i] = find(father[i]);
            }

            return father[i];
        };

        auto same_set = [&](int a, int b) -> bool
        {
            return find(a) == find(b);
        };

        auto un = [&](int a, int b) -> bool
        {
            int ua = find(a), ub = find(b);
            if (ua != ub)
            {
                father[ua] = ub;
                return true;
            }
            else
            {
                return false;
            }
        };

        int m = edgeList.size();
        vector<bool> ans(k);
        for (int i = 0, j = 0; i < k; i++)
        {
            for (; j < m && edgeList[j][2] < questions[i][2]; j++)
            {
                un(edgeList[j][0], edgeList[j][1]);
            }

            ans[questions[i][3]] = same_set(questions[i][0], questions[i][1]);
        }

        return ans;
    }
};
// @lc code=end

