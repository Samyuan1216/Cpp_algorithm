/*
 * @lc app=leetcode.cn id=839 lang=cpp
 *
 * [839] 相似字符串组
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int numSimilarGroups(vector<string>& strs)
    {
        int n = strs.size(), m = strs[0].length();
        int set = n;

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

        function<void (int, int)> un = [&](int a, int b) -> void
        {
            int ua = find(a), ub = find(b);
            if (ua != ub)
            {
                father[ua] = ub;
                set--;
            }
        };

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (find(i) != find(j))
                {
                    int diff = 0;
                    for (int k = 0; k < m && diff < 3; k++)
                    {
                        if (strs[i][k] != strs[j][k])
                        {
                            diff++;
                        }
                    }

                    if (diff == 0 || diff == 2)
                    {
                        un(i, j);
                    }
                }
            }
        }

        return set;
    }
};
// @lc code=end

