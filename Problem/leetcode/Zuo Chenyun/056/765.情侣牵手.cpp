/*
 * @lc app=leetcode.cn id=765 lang=cpp
 *
 * [765] 情侣牵手
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minSwapsCouples(vector<int>& row)
    {
        int n = row.size() / 2;
        vector<int> father(n);
        vector<int> len(n, 1);

        for (int i = 0; i < n; i++)
        {
            father[i] = i;
        }

        auto find = [&](auto &self, int i) -> int
        {
            if (i != father[i])
            {
                father[i] = self(self, father[i]);
            }

            return father[i];
        };

        auto un = [&](int a, int b) -> void
        {
            int ua = find(find, a), ub = find(find, b);

            if (ua != ub)
            {
                if (len[ua] >= len[ub])
                {
                    len[ua] += len[ub];
                    father[ub] = ua;
                }
                else
                {
                    len[ub] += len[ua];
                    father[ua] = ub;
                }
            }
        };

        for (int i = 0; i < 2 * n; i += 2)
        {
            un(row[i] / 2, row[i + 1] / 2);
        }

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            if (i == father[i])
            {
                ans += (len[i] - 1);
            }
        }

        return ans;
    }
};
// @lc code=end

